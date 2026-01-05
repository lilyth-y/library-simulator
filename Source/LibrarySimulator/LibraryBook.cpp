#include "LibraryBook.h"
#include "Kismet/GameplayStatics.h"

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
    if (!CollisionSound) return;

    // Logic: Volume based on impact magnitude
    float ImpactForce = NormalImpulse.Size();
    if (ImpactForce > 1000.0f) // Minimal threshold
    {
        float VolumeMultiplier = FMath::Clamp(ImpactForce / 10000.0f, 0.1f, 1.0f);
        UGameplayStatics::PlaySoundAtLocation(this, CollisionSound, GetActorLocation(), VolumeMultiplier);
    }
}

void ALibraryBook::Pickup_Implementation()
{
    // Logic to attach to character
    BookMesh->SetSimulatePhysics(false);
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
