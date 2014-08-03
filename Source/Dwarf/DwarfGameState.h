

#pragma once

#include "DwarfTypes.h"
#include "GameFramework/GameState.h"
#include "DwarfGameState.generated.h"
  
class ADwarfGameMode;

/**
 * 
 */
UCLASS()
class ADwarfGameState : public AGameState
{
	GENERATED_UCLASS_BODY()

    EGameplayState::Type State;

    int CoinsCollected;

    int CoinsToCollect;

    ADwarfGameMode* DwarfGameMode;

    void SetGameplayState(EGameplayState::Type State);

    void BeginPlay() OVERRIDE;

};
