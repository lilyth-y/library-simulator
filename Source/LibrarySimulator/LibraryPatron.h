#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LibraryPatron.generated.h"

UENUM(BlueprintType)
enum class EPatronState : uint8
{
    Idle        UMETA(DisplayName = "Idle"),
    Reading     UMETA(DisplayName = "Reading"),
    Rude        UMETA(DisplayName = "Rude"), // Disorganizing
    Alerted     UMETA(DisplayName = "Alerted"), // After being shushed
    Leaving     UMETA(DisplayName = "Leaving")
};

UENUM(BlueprintType)
enum class EVillainType : uint8
{
    None            UMETA(DisplayName = "Normal Patron"),
    Noisy           UMETA(DisplayName = "The Noisy"),
    SecretEater     UMETA(DisplayName = "The Secret Eater"),
    TheBoss         UMETA(DisplayName = "The Boss")
};

UCLASS()
class ALibraryPatron : public ACharacter
{
    GENERATED_BODY()

public:
    ALibraryPatron();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    EPatronState CurrentState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    EVillainType VillainType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float RudenessLevel; // 0.0 to 100.0

    UFUNCTION(BlueprintCallable, Category = "AI")
    void ChangeState(EPatronState NewState);

    // Villain Actions
    UFUNCTION(BlueprintCallable, Category = "AI|Action")
    void MakeNoise();

    UFUNCTION(BlueprintCallable, Category = "AI|Action")
    void SpawnCrumbs();

    UFUNCTION(BlueprintCallable, Category = "AI|Action")
    void SpawnPriorityTask();

    UFUNCTION(BlueprintImplementableEvent, Category = "AI")
    void OnShushed();
};
