#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LibraryBook.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "LibraryCharacter.generated.h"

UCLASS()
class ALibraryCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ALibraryCharacter();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")
    UPhysicsHandleComponent* PhysicsHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    ALibraryBook* CarriedBook;

    UFUNCTION(BlueprintCallable, Category = "Action")
    void Interact();

    UFUNCTION(BlueprintCallable, Category = "Action")
    void PickupBook(ALibraryBook* Book);

    UFUNCTION(BlueprintCallable, Category = "Action")
    void ReleaseBook();

    UFUNCTION(BlueprintCallable, Category = "Action")
    void ShushPatron();

private:
    void TraceForInteractable();
};
