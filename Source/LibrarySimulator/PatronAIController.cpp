#include "PatronAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

APatronAIController::APatronAIController()
{
}

void APatronAIController::BeginPlay()
{
    Super::BeginPlay();
    if (BehaviorTree)
    {
        RunBehaviorTree(BehaviorTree);
    }
}

void APatronAIController::ForceDesist()
{
    if (GetBlackboardComponent())
    {
        GetBlackboardComponent()->SetValueAsBool("IsRude", false);
    }
}
