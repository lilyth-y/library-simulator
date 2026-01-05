#include "LibraryPatron.h"

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
}

void ALibraryPatron::SpawnCrumbs()
{
    if (VillainType != EVillainType::SecretEater) return;

    // Logic: Spawn Crumb Actor at feet
    FVector SpawnLoc = GetActorLocation() - FVector(0,0,90); // Near floor
    // GetWorld()->SpawnActor<ACrumbActor>(SpawnLoc, ...);
    UE_LOG(LogTemp, Warning, TEXT("CRUMBS! Patron %s dropped food."), *GetName());
}

void ALibraryPatron::SpawnPriorityTask()
{
    if (VillainType != EVillainType::TheBoss) return;

    // Logic: Spawn Paper Stack Actor near Player
    UE_LOG(LogTemp, Warning, TEXT("WORK! Boss %s gave you more work."), *GetName());
}
