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
    
    UFUNCTION(BlueprintCallable, Category = "LibraryPC|Repair")
    bool ValidateBarcodeInput(int32 InputCode, const FBookData& TargetBook);

    UFUNCTION(BlueprintCallable, Category = "LibraryPC|Repair")
    void ReprintLabel(const FBookData& TargetBook);

    UFUNCTION(BlueprintImplementableEvent, Category = "LibraryPC")
    void UpdateDisplay(const FBookData& Data);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
    TArray<FBookData> LibraryDatabase;
};
