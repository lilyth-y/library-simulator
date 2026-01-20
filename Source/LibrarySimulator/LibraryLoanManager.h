#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BookTypes.h"
#include "LibraryLoanManager.generated.h"

USTRUCT(BlueprintType)
struct FBookLoanRecord
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loan")
    int32 Barcode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loan")
    FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loan")
    FString PatronName;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Loan")
    float BorrowedTimeSeconds;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Loan")
    float DueTimeSeconds;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Loan")
    bool bIsOverdue;
};

UCLASS()
class ALibraryLoanManager : public AActor
{
    GENERATED_BODY()

public:
    ALibraryLoanManager();

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loan")
    float OverdueCheckIntervalSeconds;

    UFUNCTION(BlueprintCallable, Category = "Loan")
    bool BorrowBook(const FBookData& Book, const FString& PatronName, float LoanDurationSeconds, FBookLoanRecord& OutRecord);

    UFUNCTION(BlueprintCallable, Category = "Loan")
    bool ReturnBookByBarcode(int32 Barcode, FBookLoanRecord& OutRecord);

    UFUNCTION(BlueprintCallable, Category = "Loan")
    TArray<FBookLoanRecord> GetActiveLoans() const;

    UFUNCTION(BlueprintCallable, Category = "Loan")
    TArray<FBookLoanRecord> GetOverdueLoans() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "Loan")
    void OnLoanCreated(const FBookLoanRecord& Record);

    UFUNCTION(BlueprintImplementableEvent, Category = "Loan")
    void OnLoanReturned(const FBookLoanRecord& Record);

    UFUNCTION(BlueprintImplementableEvent, Category = "Loan")
    void OnLoanOverdue(const FBookLoanRecord& Record);

private:
    UPROPERTY(VisibleAnywhere, Category = "Loan")
    TArray<FBookLoanRecord> ActiveLoans;

    float LastOverdueCheckTimeSeconds;

    void UpdateOverdues();
};
