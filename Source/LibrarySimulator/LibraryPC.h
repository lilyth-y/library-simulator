#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BookTypes.h"
#include "LibraryPC.generated.h"

UCLASS()
class ALibraryPC : public AActor
{
    GENERATED_BODY()
    
public:    
    ALibraryPC();

    UFUNCTION(BlueprintCallable, Category = "LibraryPC|Search")
    bool SearchBook(FString Title, FBookData& OutData);

    UFUNCTION(BlueprintCallable, Category = "LibraryPC|Search")
    bool SearchBookByBarcode(int32 Barcode, FBookData& OutData);
    
    UFUNCTION(BlueprintCallable, Category = "LibraryPC|Repair")
    bool ValidateBarcodeInput(int32 InputCode, const FBookData& TargetBook);

    UFUNCTION(BlueprintCallable, Category = "LibraryPC|Repair")
    void ReprintLabel(const FBookData& TargetBook);

    UFUNCTION(BlueprintCallable, Category = "LibraryPC|Database")
    bool AddBookToDatabase(const FBookData& NewBook);

    UFUNCTION(BlueprintCallable, Category = "LibraryPC|Database")
    bool RemoveBookByBarcode(int32 Barcode);

    UFUNCTION(BlueprintCallable, Category = "LibraryPC|Database")
    bool RemoveBookByTitle(const FString& Title);

    UFUNCTION(BlueprintCallable, Category = "LibraryPC|Purchase")
    bool PurchaseNewBook(const FBookData& NewBook);

    UFUNCTION(BlueprintImplementableEvent, Category = "LibraryPC")
    void UpdateDisplay(const FBookData& Data);

    UFUNCTION(BlueprintImplementableEvent, Category = "LibraryPC")
    void OnBookAdded(const FBookData& Data);

    UFUNCTION(BlueprintImplementableEvent, Category = "LibraryPC")
    void OnBookRemoved(const FBookData& Data);

    UFUNCTION(BlueprintImplementableEvent, Category = "LibraryPC")
    void OnBookPurchased(const FBookData& Data);

    UFUNCTION(BlueprintImplementableEvent, Category = "LibraryPC")
    void OnSearchFailed(const FString& Query);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
    TArray<FBookData> LibraryDatabase;
};
