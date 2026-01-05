#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystem.h"
#include "LibraryTaskManager.generated.h"

USTRUCT(BlueprintType)
struct FMissionData
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimeLimit;
};

UCLASS()
class ALibraryTaskManager : public AActor
{
    GENERATED_BODY()
    
public:    
    ALibraryTaskManager();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tasks")
    int32 MaxReturnQueueSize;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tasks")
    int32 CurrentReturnQueueSize;

    UFUNCTION(BlueprintCallable, Category = "GameLoop")
    void TriggerGameOver();

    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    USoundBase* GameOverSound; // e.g., "Avalanche" sound

    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    USoundBase* QueueFullWarningSound;

    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UParticleSystem* BookExplosionFX;

    // Configuration for the "Buried" effect
    UPROPERTY(EditAnywhere, Category = "GameLoop")
    int32 BooksToSpawnOnGameOver = 50;

    UFUNCTION(BlueprintCallable, Category = "Tasks")
    void AddBookToQueue();

    UFUNCTION(BlueprintImplementableEvent, Category = "Tasks")
    void OnGameOver();

private:
    FTimerHandle MissionSpawnTimer;
    void SpawnRandomMission();
};
