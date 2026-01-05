#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LibraryAnimInstance.generated.h"

class ALibraryCharacter;

/**
 * Production Best Practice: Custom C++ AnimInstance.
 * Logic here runs on worker threads (NativeUpdateAnimation) for performance.
 * Variables are cached to allow "Fast Path" in the AnimGraph.
 */
UCLASS()
class ULibraryAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaTime) override;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Library|Cache")
    ALibraryCharacter* CharacterRef;

    UPROPERTY(BlueprintReadOnly, Category = "Library|Cache")
    float GroundSpeed;

    UPROPERTY(BlueprintReadOnly, Category = "Library|Cache")
    bool bShouldMove;

    UPROPERTY(BlueprintReadOnly, Category = "Library|Cache")
    bool bIsCarryingBook;

    UPROPERTY(BlueprintReadOnly, Category = "Library|Cache")
    bool bIsFalling;
};
