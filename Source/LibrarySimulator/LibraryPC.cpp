#include "LibraryPC.h"

ALibraryPC::ALibraryPC()
{
    PrimaryActorTick.bCanEverTick = false;
}

bool ALibraryPC::SearchBook(FString Title, FBookData& OutData)
{
    for (const FBookData& Book : LibraryDatabase)
    {
        if (Book.Title.Equals(Title, ESearchCase::IgnoreCase))
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
    const int32 ExpectedCode = FMath::RoundToInt(TargetBook.CategoryID * 10.0f);
    const bool bHasExpectedCode = ExpectedCode > 0;
    const bool bSuccess = bHasExpectedCode ? (InputCode == ExpectedCode) : (InputCode > 0);
    
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
