#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LibraryGameInstance.generated.h"

/**
 * Phase 4 System: Boilerplate for Steam API and Persistent Settings.
 */
UCLASS()
class ULibraryGameInstance : public UGameInstance
{
    GENERATED_BODY()
    
public:
    virtual void Init() override;
    virtual void Shutdown() override;

    UFUNCTION(BlueprintCallable, Category = "System")
    void ApplyGraphicsSettings(int32 QualityLevel); // 0:Low, 3:Epic

    UPROPERTY(BlueprintReadOnly, Category = "System")
    bool bIsSteamRunning;
};
