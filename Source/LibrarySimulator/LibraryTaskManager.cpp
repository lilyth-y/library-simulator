#include "LibraryTaskManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystem.h"
#include "LibraryBook.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"

ALibraryTaskManager::ALibraryTaskManager()
{
    PrimaryActorTick.bCanEverTick = false; // Uses TimerManager, no Tick needed
    MaxReturnQueueSize = 10;
    CurrentReturnQueueSize = 0;
}

void ALibraryTaskManager::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(MissionSpawnTimer, this, &ALibraryTaskManager::SpawnRandomMission, 60.0f, true);
}

void ALibraryTaskManager::AddBookToQueue()
{
    if (CurrentReturnQueueSize >= MaxReturnQueueSize)
    {
        TriggerGameOver();
        return;
    }
    
    CurrentReturnQueueSize++;
    
    // Play Warning Sound if getting close
    if (CurrentReturnQueueSize > MaxReturnQueueSize * 0.8f && QueueFullWarningSound)
    {
        UGameplayStatics::PlaySound2D(this, QueueFullWarningSound);
    }
}

void ALibraryTaskManager::RemoveBookFromQueue()
{
    if (CurrentReturnQueueSize <= 0)
    {
        CurrentReturnQueueSize = 0;
        return;
    }

    CurrentReturnQueueSize--;
}

void ALibraryTaskManager::TriggerGameOver()
{
    UE_LOG(LogTemp, Warning, TEXT("GAME OVER: Buried in Books!"));

    // 1. Play Sound
    if (GameOverSound)
    {
        UGameplayStatics::PlaySound2D(this, GameOverSound);
    }

    // Call Blueprint Event for UI
    OnGameOver();

    // 2. Visual Chaos: Spawn falling books above player
    ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(this, 0);
    if (PlayerChar)
    {
        FVector SpawnOrigin = PlayerChar->GetActorLocation() + FVector(0, 0, 500); // Above player
        
        for (int32 i = 0; i < BooksToSpawnOnGameOver; i++)
        {
            // Note: In real blueprint, spawn BP_LibraryBook. 
            // The heavy lifting is done by the Radial Impulse below.
        }

        // 3. Physics Explosion on existing books
        TArray<AActor*> AllBooks;
        UGameplayStatics::GetAllActorsOfClass(this, ALibraryBook::StaticClass(), AllBooks);
        
        for (AActor* Actor : AllBooks)
        {
            if (ALibraryBook* Book = Cast<ALibraryBook>(Actor))
            {
                UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(Book->GetRootComponent());
                if (Prim && Prim->IsSimulatingPhysics())
                {
                    Prim->AddRadialImpulse(PlayerChar->GetActorLocation(), 1000.0f, 2000.0f, ERadialImpulseFalloff::RIF_Linear, true);
                }
            }
        }
    }
}

void ALibraryTaskManager::SpawnRandomMission()
{
    if (MissionPool.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("MissionPool is empty. No mission spawned."));
        return;
    }

    const int32 MissionIndex = FMath::RandRange(0, MissionPool.Num() - 1);
    CurrentMission = MissionPool[MissionIndex];
    OnMissionSpawned(CurrentMission);

    UE_LOG(LogTemp, Log, TEXT("New Mission Spawned: %s"), *CurrentMission.Description);
}
