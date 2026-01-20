#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LibraryNoiseManager.generated.h"

UCLASS()
class ALibraryNoiseManager : public AActor
{
    GENERATED_BODY()

public:
    ALibraryNoiseManager();

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
    float NoiseDecayPerSecond;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
    float NoiseThreshold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
    float MaxNoiseLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
    float NoiseCooldownSeconds;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noise")
    float CurrentNoiseLevel;

    UFUNCTION(BlueprintCallable, Category = "Noise")
    void ReportNoise(float Amount, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Noise")
    void ReduceNoise(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Noise")
    void ClearNoise();

    UFUNCTION(BlueprintImplementableEvent, Category = "Noise")
    void OnNoiseLevelChanged(float NewLevel);

    UFUNCTION(BlueprintImplementableEvent, Category = "Noise")
    void OnNoiseThresholdReached(float NewLevel, FVector Location);

private:
    float LastNoiseEventTimeSeconds;
};
