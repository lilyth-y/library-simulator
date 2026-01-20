#include "LibraryLoanManager.h"

ALibraryLoanManager::ALibraryLoanManager()
{
    PrimaryActorTick.bCanEverTick = true;
    OverdueCheckIntervalSeconds = 5.0f;
    LastOverdueCheckTimeSeconds = -100000.0f;
}

void ALibraryLoanManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!GetWorld())
    {
        return;
    }

    const float CurrentTimeSeconds = GetWorld()->GetTimeSeconds();
    if (OverdueCheckIntervalSeconds <= 0.0f || (CurrentTimeSeconds - LastOverdueCheckTimeSeconds) >= OverdueCheckIntervalSeconds)
    {
        LastOverdueCheckTimeSeconds = CurrentTimeSeconds;
        UpdateOverdues();
    }
}

bool ALibraryLoanManager::BorrowBook(const FBookData& Book, const FString& PatronName, float LoanDurationSeconds, FBookLoanRecord& OutRecord)
{
    if (!GetWorld() || LoanDurationSeconds <= 0.0f)
    {
        return false;
    }

    for (const FBookLoanRecord& Existing : ActiveLoans)
    {
        if (Existing.Barcode == Book.Barcode && Book.Barcode > 0)
        {
            return false;
        }
    }

    const float NowSeconds = GetWorld()->GetTimeSeconds();
    FBookLoanRecord NewRecord;
    NewRecord.Barcode = Book.Barcode;
    NewRecord.Title = Book.Title;
    NewRecord.PatronName = PatronName;
    NewRecord.BorrowedTimeSeconds = NowSeconds;
    NewRecord.DueTimeSeconds = NowSeconds + LoanDurationSeconds;
    NewRecord.bIsOverdue = false;

    ActiveLoans.Add(NewRecord);
    OutRecord = NewRecord;
    OnLoanCreated(NewRecord);
    return true;
}

bool ALibraryLoanManager::ReturnBookByBarcode(int32 Barcode, FBookLoanRecord& OutRecord)
{
    for (int32 Index = 0; Index < ActiveLoans.Num(); ++Index)
    {
        if (ActiveLoans[Index].Barcode == Barcode && Barcode > 0)
        {
            OutRecord = ActiveLoans[Index];
            ActiveLoans.RemoveAt(Index);
            OnLoanReturned(OutRecord);
            return true;
        }
    }

    return false;
}

TArray<FBookLoanRecord> ALibraryLoanManager::GetActiveLoans() const
{
    return ActiveLoans;
}

TArray<FBookLoanRecord> ALibraryLoanManager::GetOverdueLoans() const
{
    TArray<FBookLoanRecord> Overdues;
    for (const FBookLoanRecord& Record : ActiveLoans)
    {
        if (Record.bIsOverdue)
        {
            Overdues.Add(Record);
        }
    }
    return Overdues;
}

void ALibraryLoanManager::UpdateOverdues()
{
    if (!GetWorld())
    {
        return;
    }

    const float CurrentTimeSeconds = GetWorld()->GetTimeSeconds();
    for (FBookLoanRecord& Record : ActiveLoans)
    {
        if (!Record.bIsOverdue && CurrentTimeSeconds >= Record.DueTimeSeconds)
        {
            Record.bIsOverdue = true;
            OnLoanOverdue(Record);
        }
    }
}
