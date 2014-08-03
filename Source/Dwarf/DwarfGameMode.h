

#pragma once

#include "DwarfTypes.h"
#include "GameFramework/GameMode.h"
#include "DwarfGameMode.generated.h"

class ADwarfCharacter;

/**
 * 
 */
UCLASS(minimalapi)
class ADwarfGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()        

    /** Player Dwarf Character Pawn **/
    TSubclassOf<ADwarfCharacter> DwarfCharacterClass; 
                          
    /** Sets up game state **/
    virtual void StartPlay() OVERRIDE;

    void StartPlayer();                          

    void OnGameplayStateChange(EGameplayState::Type NewState);
                                                                             
};
