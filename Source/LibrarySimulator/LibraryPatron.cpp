#include "LibraryPatron.h"
#include "Kismet/GameplayStatics.h"
#include "LibraryNoiseManager.h"
#include "LibraryTrashManager.h"

ALibraryPatron::ALibraryPatron()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentState = EPatronState::Idle;
    VillainType = EVillainType::None;
    RudenessLevel = 0.0f;
}

void ALibraryPatron::ChangeState(EPatronState NewState)
{
    CurrentState = NewState;
}

void ALibraryPatron::MakeNoise()
{
    if (VillainType != EVillainType::Noisy) return;
    
    // Logic: Play basic sound range.
    UE_LOG(LogTemp, Warning, TEXT("NOISE! Patron %s is being loud."), *GetName());
    // Actual implementation would involve spawning audio component or reporting noise event to GameState

    TArray<AActor*> NoiseManagers;
    UGameplayStatics::GetAllActorsOfClass(this, ALibraryNoiseManager::StaticClass(), NoiseManagers);
    if (NoiseManagers.Num() > 0)
    {
        if (ALibraryNoiseManager* NoiseManager = Cast<ALibraryNoiseManager>(NoiseManagers[0]))
        {
            const float NoiseAmount = FMath::Clamp(RudenessLevel / 50.0f, 0.2f, 2.0f);
            NoiseManager->ReportNoise(NoiseAmount, GetActorLocation());
        }
    }
}

void ALibraryPatron::SpawnCrumbs()
{
    if (VillainType != EVillainType::SecretEater) return;

    // Logic: Spawn Crumb Actor at feet
    FVector SpawnLoc = GetActorLocation() - FVector(0,0,90); // Near floor
    // GetWorld()->SpawnActor<ACrumbActor>(SpawnLoc, ...);
    UE_LOG(LogTemp, Warning, TEXT("CRUMBS! Patron %s dropped food."), *GetName());

    TArray<AActor*> TrashManagers;
    UGameplayStatics::GetAllActorsOfClass(this, ALibraryTrashManager::StaticClass(), TrashManagers);
    if (TrashManagers.Num() > 0)
    {
        if (ALibraryTrashManager* TrashManager = Cast<ALibraryTrashManager>(TrashManagers[0]))
        {
            TrashManager->SpawnTrash(SpawnLoc, TEXT("Crumbs"));
        }
    }
}

void ALibraryPatron::SpawnPriorityTask()
{
    if (VillainType != EVillainType::TheBoss) return;

    // Logic: Spawn Paper Stack Actor near Player
    UE_LOG(LogTemp, Warning, TEXT("WORK! Boss %s gave you more work."), *GetName());
}
