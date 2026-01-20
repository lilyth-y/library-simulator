#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "BookTypes.h"
#include "BookInterface.h"
#include "LibraryBook.generated.h"

class UPrimitiveComponent;
class USoundBase;
class UStaticMeshComponent;

UCLASS()
class ALibraryBook : public AActor, public IBookInterface
{
    GENERATED_BODY()
    
public:    
    ALibraryBook();

protected:
    virtual void BeginPlay() override;

public:    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* BookMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundBase* CollisionSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Book Data")
    FBookData BookData;

    // IBookInterface Implementation
    virtual void Pickup_Implementation() override;
    virtual void CheckStatus_Implementation() override;
    virtual void ApplyRepair_Implementation() override;

    UFUNCTION(BlueprintCallable, Category = "Book")
    void SetHighlight(bool bEnabled);

    UFUNCTION(BlueprintImplementableEvent, Category = "Book")
    void OnBookImpact(float ImpactForce, FVector ImpactLocation);

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
