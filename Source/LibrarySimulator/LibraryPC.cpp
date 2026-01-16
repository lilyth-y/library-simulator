#include "LibraryPC.h"

ALibraryPC::ALibraryPC()
{
    PrimaryActorTick.bCanEverTick = false;
}

bool ALibraryPC::SearchBook(FString Title, FBookData& OutData)
{
    const FString Query = Title.TrimStartAndEnd();
    if (Query.IsEmpty())
    {
        return false;
    }

    for (const FBookData& Book : LibraryDatabase)
    {
        if (Book.Title.Equals(Query, ESearchCase::IgnoreCase))
        {
            OutData = Book;
            UpdateDisplay(OutData);
            return true; 
        }
    }

    for (const FBookData& Book : LibraryDatabase)
    {
        if (Book.Title.Contains(Query, ESearchCase::IgnoreCase))
        {
            OutData = Book;
            UpdateDisplay(OutData);
            return true;
        }
    }
    return false;
}

bool ALibraryPC::ValidateBarcodeInput(int32 InputCode, const FBookData& TargetBook)
{
    const bool bHasBarcode = TargetBook.Barcode > 0;
    const bool bSuccess = bHasBarcode ? (InputCode == TargetBook.Barcode) : (InputCode > 0);
    
    if (bSuccess)
    {
        UE_LOG(LogTemp, Log, TEXT("Barcode Validated for %s"), *TargetBook.Title);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Barcode Validation Failed"));
    }
    return bSuccess;
}

void ALibraryPC::ReprintLabel(const FBookData& TargetBook)
{
    // Logic: Spawn a 'BP_Label' actor at the printer output location
    UE_LOG(LogTemp, Log, TEXT("Printing Label for: %s | Category: %f"), *TargetBook.Title, TargetBook.CategoryID);
    // GetWorld()->SpawnActor...
}
