#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatronAIController.generated.h"

UCLASS()
class APatronAIController : public AAIController
{
    GENERATED_BODY()

public:
    APatronAIController();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, Category = "AI")
    class UBehaviorTree* BehaviorTree;

    UFUNCTION(BlueprintCallable, Category = "AI")
    void ForceDesist(); // Stop rude behavior
};
