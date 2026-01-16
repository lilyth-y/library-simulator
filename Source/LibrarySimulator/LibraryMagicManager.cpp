#include "LibraryMagicManager.h"
#include "Kismet/GameplayStatics.h"
#include "LibraryBook.h"
#include "LibraryShelf.h"

ALibraryMagicManager::ALibraryMagicManager()
{
    PrimaryActorTick.bCanEverTick = false;
    MagicCooldownSeconds = 2.0f;
    LastMagicTimeSeconds = -100000.0f;
}

bool ALibraryMagicManager::LocateBookByBarcode(int32 Barcode, FVector& OutLocation, ALibraryBook*& OutBook)
{
    OutBook = nullptr;
    if (Barcode <= 0 || !GetWorld())
    {
        return false;
    }

    TArray<AActor*> BookActors;
    UGameplayStatics::GetAllActorsOfClass(this, ALibraryBook::StaticClass(), BookActors);
    for (AActor* Actor : BookActors)
    {
        ALibraryBook* Book = Cast<ALibraryBook>(Actor);
        if (Book && Book->BookData.Barcode == Barcode)
        {
            OutBook = Book;
            OutLocation = Book->GetActorLocation();
            OnBookLocated(Book, OutLocation);
            return true;
        }
    }

    return false;
}

bool ALibraryMagicManager::LocateBookByTitle(const FString& Title, FVector& OutLocation, ALibraryBook*& OutBook)
{
    OutBook = nullptr;
    const FString Query = Title.TrimStartAndEnd();
    if (Query.IsEmpty() || !GetWorld())
    {
        return false;
    }

    TArray<AActor*> BookActors;
    UGameplayStatics::GetAllActorsOfClass(this, ALibraryBook::StaticClass(), BookActors);
    for (AActor* Actor : BookActors)
    {
        ALibraryBook* Book = Cast<ALibraryBook>(Actor);
        if (Book && Book->BookData.Title.Equals(Query, ESearchCase::IgnoreCase))
        {
            OutBook = Book;
            OutLocation = Book->GetActorLocation();
            OnBookLocated(Book, OutLocation);
            return true;
        }
    }

    return false;
}

bool ALibraryMagicManager::LevitateBook(ALibraryBook* Book, float DurationSeconds)
{
    if (!Book || DurationSeconds <= 0.0f || !IsMagicReady())
    {
        return false;
    }

    MarkMagicUsed();
    OnLevitateBook(Book, DurationSeconds);
    return true;
}

bool ALibraryMagicManager::AutoShelfBook(ALibraryBook* Book, ALibraryShelf* Shelf)
{
    if (!Book || !Shelf || !IsMagicReady())
    {
        return false;
    }

    MarkMagicUsed();
    OnAutoShelfBook(Book, Shelf);
    return true;
}

bool ALibraryMagicManager::IsMagicReady() const
{
    const float CurrentTimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
    return (CurrentTimeSeconds - LastMagicTimeSeconds) >= MagicCooldownSeconds;
}

void ALibraryMagicManager::MarkMagicUsed()
{
    LastMagicTimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
}
