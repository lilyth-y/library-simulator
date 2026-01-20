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
        OnSearchFailed(Query);
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
    OnSearchFailed(Query);
    return false;
}

bool ALibraryPC::SearchBookByBarcode(int32 Barcode, FBookData& OutData)
{
    if (Barcode <= 0)
    {
        OnSearchFailed(FString::FromInt(Barcode));
        return false;
    }

    for (const FBookData& Book : LibraryDatabase)
    {
        if (Book.Barcode == Barcode)
        {
            OutData = Book;
            UpdateDisplay(OutData);
            return true;
        }
    }

    OnSearchFailed(FString::FromInt(Barcode));
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

bool ALibraryPC::AddBookToDatabase(const FBookData& NewBook)
{
    if (NewBook.Barcode > 0)
    {
        for (const FBookData& Book : LibraryDatabase)
        {
            if (Book.Barcode == NewBook.Barcode)
            {
                return false;
            }
        }
    }

    if (!NewBook.Title.IsEmpty())
    {
        for (const FBookData& Book : LibraryDatabase)
        {
            if (Book.Title.Equals(NewBook.Title, ESearchCase::IgnoreCase))
            {
                return false;
            }
        }
    }

    LibraryDatabase.Add(NewBook);
    OnBookAdded(NewBook);
    return true;
}

bool ALibraryPC::RemoveBookByBarcode(int32 Barcode)
{
    for (int32 Index = 0; Index < LibraryDatabase.Num(); ++Index)
    {
        if (LibraryDatabase[Index].Barcode == Barcode && Barcode > 0)
        {
            FBookData Removed = LibraryDatabase[Index];
            LibraryDatabase.RemoveAt(Index);
            OnBookRemoved(Removed);
            return true;
        }
    }

    return false;
}

bool ALibraryPC::RemoveBookByTitle(const FString& Title)
{
    const FString Query = Title.TrimStartAndEnd();
    if (Query.IsEmpty())
    {
        return false;
    }

    for (int32 Index = 0; Index < LibraryDatabase.Num(); ++Index)
    {
        if (LibraryDatabase[Index].Title.Equals(Query, ESearchCase::IgnoreCase))
        {
            FBookData Removed = LibraryDatabase[Index];
            LibraryDatabase.RemoveAt(Index);
            OnBookRemoved(Removed);
            return true;
        }
    }

    return false;
}

bool ALibraryPC::PurchaseNewBook(const FBookData& NewBook)
{
    if (AddBookToDatabase(NewBook))
    {
        OnBookPurchased(NewBook);
        return true;
    }

    return false;
}
