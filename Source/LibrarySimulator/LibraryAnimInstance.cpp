#include "LibraryAnimInstance.h"
#include "LibraryCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ULibraryAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    CharacterRef = Cast<ALibraryCharacter>(TryGetPawnOwner());
}

void ULibraryAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    if (!CharacterRef)
    {
        CharacterRef = Cast<ALibraryCharacter>(TryGetPawnOwner());
    }

    if (CharacterRef)
    {
        // Fast Path Variable Updates
        FVector Velocity = CharacterRef->GetVelocity();
        Velocity.Z = 0;
        GroundSpeed = Velocity.Size();

        bShouldMove = (GroundSpeed > 3.0f) && (CharacterRef->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0);
        bIsCarryingBook = (CharacterRef->GetCarriedBook() != nullptr);
        bIsFalling = CharacterRef->GetCharacterMovement()->IsFalling();
    }
}
