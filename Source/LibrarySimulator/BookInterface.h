#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BookInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UBookInterface : public UInterface
{
    GENERATED_BODY()
};

class IBookInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
    void Pickup();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
    void CheckStatus();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
    void ApplyRepair();
};
