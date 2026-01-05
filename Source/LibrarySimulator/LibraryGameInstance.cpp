#include "LibraryGameInstance.h"
#include "GameFramework/GameUserSettings.h"

void ULibraryGameInstance::Init()
{
    Super::Init();
    
    // Steam API Initialization Placeholder
    // if (SteamAPI_Init()) ...
    bIsSteamRunning = false; // Set to check actual API later
    
    UE_LOG(LogTemp, Log, TEXT("LibraryGameInstance Initialized"));
}

void ULibraryGameInstance::Shutdown()
{
    // SteamAPI_Shutdown();
    Super::Shutdown();
}

void ULibraryGameInstance::ApplyGraphicsSettings(int32 QualityLevel)
{
    UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
    if (Settings)
    {
        Settings->SetOverallScalabilityLevel(QualityLevel);
        Settings->SetFrameRateLimit(QualityLevel == 0 ? 30.0f : 0.0f); // Cap FPS on low settings
        Settings->ApplySettings(false);
        Settings->SaveSettings();
        
        UE_LOG(LogTemp, Log, TEXT("Graphics Settings Applied: Level %d"), QualityLevel);
    }
}
