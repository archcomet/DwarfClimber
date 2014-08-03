

#include "Dwarf.h"     
#include "DwarfCharacter.h"
#include "DwarfSpectatorPawn.h"
#include "DwarfPlayerController.h"
#include "DwarfGameMode.h"  
#include "DwarfGameState.h"
#include "DwarfHUD.h"

ADwarfGameMode::ADwarfGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
    PlayerControllerClass = ADwarfPlayerController::StaticClass();
    DefaultPawnClass = ADwarfSpectatorPawn::StaticClass();
    GameStateClass = ADwarfGameState::StaticClass();

    static ConstructorHelpers::FObjectFinder<UBlueprint> DwarfCharacterBlueprint(TEXT("Blueprint'/Game/Blueprints/Dwarf/BP_DwarfCharacter.BP_DwarfCharacter'"));
    if (DwarfCharacterBlueprint.Object != NULL)
    {
        DwarfCharacterClass = (UClass*)DwarfCharacterBlueprint.Object->GeneratedClass;
    }

    static ConstructorHelpers::FObjectFinder<UBlueprint> DwarfHUDBlueprint(TEXT("Blueprint'/Game/Blueprints/HUD/BP_DwarfHUD.BP_DwarfHUD'"));
	if (DwarfHUDBlueprint.Object != NULL)
	{
		HUDClass = (UClass*)DwarfHUDBlueprint.Object->GeneratedClass;
	}
}

void ADwarfGameMode::StartPlay()
{
    AGameMode::StartPlay();            
    ADwarfGameState* DwarfGameState = GetGameState<ADwarfGameState>();
    DwarfGameState->DwarfGameMode = this;
    DwarfGameState->SetGameplayState(EGameplayState::Type::Starting);    
}

void ADwarfGameMode::OnGameplayStateChange(EGameplayState::Type NewState)
{
    switch (NewState)
    {
    case EGameplayState::Type::Playing:
        StartPlayer();
        break;
    }
}

void ADwarfGameMode::StartPlayer()
{
    ADwarfPlayerController* DwarfPlayerController = Cast<ADwarfPlayerController>(GetWorld()->GetFirstPlayerController());
    if (DwarfPlayerController)
    {
        DwarfPlayerController->DwarfCharacterClass = DwarfCharacterClass;
        DwarfPlayerController->SetSpawnSpot(FindPlayerStart(DwarfPlayerController));
        DwarfPlayerController->Respawn();
    }
}