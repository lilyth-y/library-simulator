#include "LibraryBook.h"
#include "Kismet/GameplayStatics.h"
#include "LibraryNoiseManager.h"

ALibraryBook::ALibraryBook()
{
    PrimaryActorTick.bCanEverTick = false; // Physics handled by engine, events by interface

    BookMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BookMesh"));
    RootComponent = BookMesh;
    BookMesh->SetSimulatePhysics(true);
    
    // Physics Optimization: Damping helps stacks settle and sleep
    BookMesh->SetSimulatePhysics(true);
    
    // Physics Optimization: Damping helps stacks settle and sleep
    BookMesh->SetLinearDamping(0.5f);
    BookMesh->SetAngularDamping(0.5f);

    // Dynamic Audio Binding
    BookMesh->SetNotifyRigidBodyCollision(true);
    BookMesh->OnComponentHit.AddDynamic(this, &ALibraryBook::OnHit);
}

void ALibraryBook::BeginPlay()
{
    Super::BeginPlay();
    // Initialize random data if needed
}

void ALibraryBook::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    const float ImpactForce = NormalImpulse.Size();

    if (CollisionSound && ImpactForce > 1000.0f)
    {
        const float VolumeMultiplier = FMath::Clamp(ImpactForce / 10000.0f, 0.1f, 1.0f);
        UGameplayStatics::PlaySoundAtLocation(this, CollisionSound, GetActorLocation(), VolumeMultiplier);
    }

    if (ImpactForce > 0.0f)
    {
        OnBookImpact(ImpactForce, GetActorLocation());
    }

    TArray<AActor*> NoiseManagers;
    UGameplayStatics::GetAllActorsOfClass(this, ALibraryNoiseManager::StaticClass(), NoiseManagers);
    if (NoiseManagers.Num() > 0)
    {
        if (ALibraryNoiseManager* NoiseManager = Cast<ALibraryNoiseManager>(NoiseManagers[0]))
        {
            const float NoiseAmount = FMath::Clamp(ImpactForce / 5000.0f, 0.1f, 2.0f);
            NoiseManager->ReportNoise(NoiseAmount, GetActorLocation());
        }
    }
}

void ALibraryBook::Pickup_Implementation()
{
    // Logic to attach to character
    BookMesh->SetSimulatePhysics(false);
    BookData.bIsBeingRelocated = true;
    BookData.bIsBeingCarried = true;
}

void ALibraryBook::CheckStatus_Implementation()
{
    // Logic to show UI widget
    UE_LOG(LogTemp, Log, TEXT("Book: %s, Status: %d"), *BookData.Title, (int32)BookData.Status);
}

void ALibraryBook::ApplyRepair_Implementation()
{
    if (BookData.Status != EBookStatus::Normal)
    {
        BookData.Status = EBookStatus::Normal;
        UE_LOG(LogTemp, Log, TEXT("Book Repaired: %s"), *BookData.Title);
    }
}

void ALibraryBook::SetHighlight(bool bEnabled)
{
    BookMesh->SetRenderCustomDepth(bEnabled);
}
