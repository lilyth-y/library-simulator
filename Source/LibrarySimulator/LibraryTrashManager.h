#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LibraryTrashManager.generated.h"

USTRUCT(BlueprintType)
struct FTrashInstance
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trash")
    int32 TrashId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trash")
    FString TrashType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trash")
    FVector Location;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trash")
    float SpawnTimeSeconds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trash")
    float LifetimeSeconds;
};

UCLASS()
class ALibraryTrashManager : public AActor
{
    GENERATED_BODY()

public:
    ALibraryTrashManager();

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trash")
    float DefaultLifetimeSeconds;

    UFUNCTION(BlueprintCallable, Category = "Trash")
    int32 SpawnTrash(FVector Location, const FString& TrashType);

    UFUNCTION(BlueprintCallable, Category = "Trash")
    bool CleanTrash(int32 TrashId);

    UFUNCTION(BlueprintCallable, Category = "Trash")
    void CleanAllTrash();

    UFUNCTION(BlueprintCallable, Category = "Trash")
    TArray<FTrashInstance> GetActiveTrash() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "Trash")
    void OnTrashSpawned(const FTrashInstance& Trash);

    UFUNCTION(BlueprintImplementableEvent, Category = "Trash")
    void OnTrashCleaned(const FTrashInstance& Trash);

    UFUNCTION(BlueprintImplementableEvent, Category = "Trash")
    void OnTrashExpired(const FTrashInstance& Trash);

private:
    int32 NextTrashId;

    UPROPERTY(VisibleAnywhere, Category = "Trash")
    TArray<FTrashInstance> ActiveTrash;
};
