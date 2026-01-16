#include "StackStabilityComponent.h"
#include "GameFramework/Actor.h"
#include "LibraryBook.h"

UStackStabilityComponent::UStackStabilityComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    HeightThreshold = 100.0f; 
    StabilityThreshold = 10.0f; // CM deviation allowed
    CollapseCooldownSeconds = 1.0f;
    LastCollapseTimeSeconds = -100000.0f;
}

void UStackStabilityComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UStackStabilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    CheckStability();
}

void UStackStabilityComponent::CheckStability()
{
    if (!IsStackStable())
    {
        const float CurrentTimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
        if (CurrentTimeSeconds - LastCollapseTimeSeconds < CollapseCooldownSeconds)
        {
            return;
        }
        LastCollapseTimeSeconds = CurrentTimeSeconds;

        OnStackCollapse.Broadcast();
        
        // Add physics impulse to simulate collapse
        TArray<AActor*> Stack = GetStackedBooks();
        for (AActor* Actor : Stack)
        {
            UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
            if (PrimComp)
            {
                PrimComp->AddRadialImpulse(GetOwner()->GetActorLocation(), 500.0f, 200.0f, ERadialImpulseFalloff::RIF_Linear, true);
            }
        }
    }
}

float UStackStabilityComponent::CalculateStackCenterOfMass(const TArray<AActor*>& Stack, FVector& OutCoM)
{
    if (Stack.Num() == 0) return 0.0f;

    FVector TotalWeightedLoc = FVector::ZeroVector;
    float TotalWeight = 0.0f;

    for (AActor* Actor : Stack)
    {
        ALibraryBook* Book = Cast<ALibraryBook>(Actor);
        float Weight = (Book) ? Book->BookData.StackWeight : 1.0f;

        TotalWeightedLoc += Actor->GetActorLocation() * Weight;
        TotalWeight += Weight;
    }

    if (TotalWeight > 0.0f)
    {
        OutCoM = TotalWeightedLoc / TotalWeight;
    }
    
    return TotalWeight;
}

bool UStackStabilityComponent::IsStackStable()
{
    TArray<AActor*> Stack = GetStackedBooks();
    if (Stack.Num() == 0) return true; // Empty stack is stable
    if (HeightThreshold > 0.0f && Stack.Num() > HeightThreshold)
    {
        return false;
    }

    FVector CoM;
    float TotalWeight = CalculateStackCenterOfMass(Stack, CoM);
    if (TotalWeight == 0.0f) return true;

    // Project CoM found to XY plane relative to Base
    FVector BaseLoc = GetOwner()->GetActorLocation();
    float DistSquared = FVector::DistSquared2D(BaseLoc, CoM);

    return DistSquared <= (StabilityThreshold * StabilityThreshold);
}

TArray<AActor*> UStackStabilityComponent::GetStackedBooks()
{
    TArray<AActor*> StackedBooks;
    
    // Logic: Get Overlapping Actors of Class ALibraryBook
    // Filter recursively upwards? For now, just get immediate overlaps logic placeholder
    GetOwner()->GetOverlappingActors(StackedBooks, ALibraryBook::StaticClass());
    
    return StackedBooks;
}
