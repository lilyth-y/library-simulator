#pragma once

#include "CoreMinimal.h"
#include "BookTypes.generated.h"

UENUM(BlueprintType)
enum class EBookStatus : uint8
{
    Normal          UMETA(DisplayName = "Normal"),
    DamagedLabel    UMETA(DisplayName = "Damaged Label"),
    DamagedBarcode  UMETA(DisplayName = "Damaged Barcode")
};

USTRUCT(BlueprintType)
struct FBookData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Book")
    FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Book")
    float CategoryID; // KDC format

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Book")
    EBookStatus Status;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Book")
    float StackWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Book")
    int32 Barcode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Book")
    int32 DesignatedShelfID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Book")
    bool bIsBeingRelocated;

    FBookData()
        : Title("Unknown")
        , CategoryID(0.0f)
        , Status(EBookStatus::Normal)
        , StackWeight(1.0f)
        , Barcode(-1)
        , DesignatedShelfID(-1)
        , bIsBeingRelocated(false)
    {}
};
