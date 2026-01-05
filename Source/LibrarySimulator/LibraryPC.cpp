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
            return true; 
        }
    }
    return false;
}

bool ALibraryPC::ValidateBarcodeInput(int32 InputCode, const FBookData& TargetBook)
{
    // In a real system, we might check a hidden ID.
    // For now, let's assume valid if input matches a hash or simple check.
    // Simplifying: Check if InputCode matches (int)CategoryID * 10 or similar logic
    // But better: Just check against a known 'Correct' code if we had it.
    
    // Placeholder logic:
    bool bSuccess = (InputCode > 0); 
    
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
