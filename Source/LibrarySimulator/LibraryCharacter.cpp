#include "LibraryCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "LibraryBook.h"

ALibraryCharacter::ALibraryCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Production Best Practice: Decouple rotation from camera for smooth locomotion
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true; 
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f); // Smooth rotation

    // Interaction tweak: Slower movement when carrying (Simulated via WalkSpeed)
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f; // Sharp stops for precision
    
    // Network Optimization
    GetCharacterMovement()->NetworkSmoothingMode = ENetworkSmoothingMode::Linear;

    PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
    CarriedBook = nullptr;
}

void ALibraryCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ALibraryCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (PhysicsHandle && CarriedBook)
    {
        FVector TargetLocation = GetActorLocation() + (GetActorForwardVector() * 100.0f);
        PhysicsHandle->SetTargetLocation(TargetLocation);
    }
}

void ALibraryCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ALibraryCharacter::Interact);
}

void ALibraryCharacter::Interact()
{
    if (!PhysicsHandle) return;

    if (CarriedBook)
    {
        ReleaseBook();
    }
    else
    {
        TraceForInteractable();
    }
}

void ALibraryCharacter::PickupBook(ALibraryBook* Book)
{
    if (!Book || !PhysicsHandle) return;

    CarriedBook = Book;

    // Best Practice: Soft handling for smooth carrying
    PhysicsHandle->LinearDamping = 200.0f;
    PhysicsHandle->LinearStiffness = 750.0f;
    PhysicsHandle->AngularDamping = 500.0f; 
    PhysicsHandle->AngularStiffness = 1500.0f;
    PhysicsHandle->InterpolationSpeed = 50.0f; 

    PhysicsHandle->GrabComponentAtLocationWithRotation(
        Book->BookMesh,
        NAME_None,
        Book->GetActorLocation(),
        Book->GetActorRotation()
    );
    
    // Disable collision with pawn so we don't trip over it
    Book->BookMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}

void ALibraryCharacter::ReleaseBook()
{
    if (!PhysicsHandle || !CarriedBook) return;

    PhysicsHandle->ReleaseComponent();
    CarriedBook->BookMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    CarriedBook = nullptr;
}

void ALibraryCharacter::ShushPatron()
{
    // Logic to trace for patron and call their OnShushed interface/function
}

void ALibraryCharacter::TraceForInteractable()
{
    FVector Start = GetActorLocation();
    FVector End = Start + (GetActorForwardVector() * 200.0f);
    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
    {
        ALibraryBook* Book = Cast<ALibraryBook>(HitResult.GetActor());
        if (Book)
        {
            PickupBook(Book);
        }
    }
}
