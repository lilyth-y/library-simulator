#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StackStabilityComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStackCollapse);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UStackStabilityComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UStackStabilityComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stability")
    float HeightThreshold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stability")
    float StabilityThreshold;

    UPROPERTY(BlueprintAssignable, Category = "Stability")
    FOnStackCollapse OnStackCollapse;

private:
    void CheckStability();
    float CalculateStackCenterOfMass(FVector& OutCoM);
    
    // Returns true if the stack is stable (CoM is within support radius)
    bool IsStackStable();
    
    TArray<AActor*> GetStackedBooks();
};
