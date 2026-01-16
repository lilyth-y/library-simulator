#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LibraryMagicManager.generated.h"

class ALibraryBook;
class ALibraryShelf;

UCLASS()
class ALibraryMagicManager : public AActor
{
    GENERATED_BODY()

public:
    ALibraryMagicManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
    float MagicCooldownSeconds;

    UFUNCTION(BlueprintCallable, Category = "Magic")
    bool LocateBookByBarcode(int32 Barcode, FVector& OutLocation, ALibraryBook*& OutBook);

    UFUNCTION(BlueprintCallable, Category = "Magic")
    bool LocateBookByTitle(const FString& Title, FVector& OutLocation, ALibraryBook*& OutBook);

    UFUNCTION(BlueprintCallable, Category = "Magic")
    bool LevitateBook(ALibraryBook* Book, float DurationSeconds);

    UFUNCTION(BlueprintCallable, Category = "Magic")
    bool AutoShelfBook(ALibraryBook* Book, ALibraryShelf* Shelf);

    UFUNCTION(BlueprintImplementableEvent, Category = "Magic")
    void OnBookLocated(ALibraryBook* Book, FVector Location);

    UFUNCTION(BlueprintImplementableEvent, Category = "Magic")
    void OnLevitateBook(ALibraryBook* Book, float DurationSeconds);

    UFUNCTION(BlueprintImplementableEvent, Category = "Magic")
    void OnAutoShelfBook(ALibraryBook* Book, ALibraryShelf* Shelf);

private:
    float LastMagicTimeSeconds;
    bool IsMagicReady() const;
    void MarkMagicUsed();
};
