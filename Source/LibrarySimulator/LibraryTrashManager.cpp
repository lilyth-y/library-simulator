#include "LibraryTrashManager.h"

ALibraryTrashManager::ALibraryTrashManager()
{
    PrimaryActorTick.bCanEverTick = true;
    DefaultLifetimeSeconds = 120.0f;
    NextTrashId = 1;
}

void ALibraryTrashManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!GetWorld())
    {
        return;
    }

    const float CurrentTimeSeconds = GetWorld()->GetTimeSeconds();
    for (int32 Index = ActiveTrash.Num() - 1; Index >= 0; --Index)
    {
        const FTrashInstance& Trash = ActiveTrash[Index];
        if (Trash.LifetimeSeconds > 0.0f && (CurrentTimeSeconds - Trash.SpawnTimeSeconds) >= Trash.LifetimeSeconds)
        {
            FTrashInstance ExpiredTrash = Trash;
            ActiveTrash.RemoveAt(Index);
            OnTrashExpired(ExpiredTrash);
        }
    }
}

int32 ALibraryTrashManager::SpawnTrash(FVector Location, const FString& TrashType)
{
    if (!GetWorld())
    {
        return INDEX_NONE;
    }

    FTrashInstance NewTrash;
    NewTrash.TrashId = NextTrashId++;
    NewTrash.TrashType = TrashType;
    NewTrash.Location = Location;
    NewTrash.SpawnTimeSeconds = GetWorld()->GetTimeSeconds();
    NewTrash.LifetimeSeconds = DefaultLifetimeSeconds;

    ActiveTrash.Add(NewTrash);
    OnTrashSpawned(NewTrash);
    return NewTrash.TrashId;
}

bool ALibraryTrashManager::CleanTrash(int32 TrashId)
{
    for (int32 Index = 0; Index < ActiveTrash.Num(); ++Index)
    {
        if (ActiveTrash[Index].TrashId == TrashId)
        {
            FTrashInstance CleanedTrash = ActiveTrash[Index];
            ActiveTrash.RemoveAt(Index);
            OnTrashCleaned(CleanedTrash);
            return true;
        }
    }

    return false;
}

void ALibraryTrashManager::CleanAllTrash()
{
    for (const FTrashInstance& Trash : ActiveTrash)
    {
        OnTrashCleaned(Trash);
    }
    ActiveTrash.Reset();
}

TArray<FTrashInstance> ALibraryTrashManager::GetActiveTrash() const
{
    return ActiveTrash;
}
