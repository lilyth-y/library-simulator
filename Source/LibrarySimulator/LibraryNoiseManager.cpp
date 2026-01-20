#include "LibraryNoiseManager.h"

ALibraryNoiseManager::ALibraryNoiseManager()
{
    PrimaryActorTick.bCanEverTick = true;
    NoiseDecayPerSecond = 0.5f;
    NoiseThreshold = 3.0f;
    MaxNoiseLevel = 5.0f;
    NoiseCooldownSeconds = 1.0f;
    CurrentNoiseLevel = 0.0f;
    LastNoiseEventTimeSeconds = -100000.0f;
}

void ALibraryNoiseManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CurrentNoiseLevel <= 0.0f)
    {
        return;
    }

    const float NewNoiseLevel = FMath::Max(0.0f, CurrentNoiseLevel - (NoiseDecayPerSecond * DeltaTime));
    if (!FMath::IsNearlyEqual(NewNoiseLevel, CurrentNoiseLevel))
    {
        CurrentNoiseLevel = NewNoiseLevel;
        OnNoiseLevelChanged(CurrentNoiseLevel);
    }
}

void ALibraryNoiseManager::ReportNoise(float Amount, FVector Location)
{
    if (Amount <= 0.0f)
    {
        return;
    }

    const float PreviousNoiseLevel = CurrentNoiseLevel;
    CurrentNoiseLevel = FMath::Clamp(CurrentNoiseLevel + Amount, 0.0f, MaxNoiseLevel);
    OnNoiseLevelChanged(CurrentNoiseLevel);

    if (CurrentNoiseLevel >= NoiseThreshold)
    {
        const bool bCrossedThreshold = PreviousNoiseLevel < NoiseThreshold;
        const float CurrentTimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
        const bool bCooldownReady = (CurrentTimeSeconds - LastNoiseEventTimeSeconds) >= NoiseCooldownSeconds;

        if (bCrossedThreshold || bCooldownReady)
        {
            LastNoiseEventTimeSeconds = CurrentTimeSeconds;
            OnNoiseThresholdReached(CurrentNoiseLevel, Location);
        }
    }
}

void ALibraryNoiseManager::ReduceNoise(float Amount)
{
    if (Amount <= 0.0f)
    {
        return;
    }

    CurrentNoiseLevel = FMath::Max(0.0f, CurrentNoiseLevel - Amount);
    OnNoiseLevelChanged(CurrentNoiseLevel);
}

void ALibraryNoiseManager::ClearNoise()
{
    CurrentNoiseLevel = 0.0f;
    OnNoiseLevelChanged(CurrentNoiseLevel);
}
