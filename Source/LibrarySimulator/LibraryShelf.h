#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "LibraryShelf.generated.h"

class ALibraryBook;

UCLASS()
class ALibraryShelf : public AActor
{
    GENERATED_BODY()
    
public:    
    ALibraryShelf();

protected:
    virtual void BeginPlay() override;

public:    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* ShelfMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* PlacementTrigger;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Categorization")
    int32 ShelfCategoryID; // e.g., 100 for Philosophy

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Categorization")
    int32 CategoryRange; // e.g., 100 range covers 100-199

    UFUNCTION(BlueprintImplementableEvent, Category = "Categorization")
    void OnShelfPlacementEvaluated(ALibraryBook* Book, bool bCorrectShelf);

    UFUNCTION()
    void OnBookPlaced(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
