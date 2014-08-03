

#include "Dwarf.h"
#include "DwarfGold.h"
#include "DwarfGameMode.h"
#include "DwarfGameState.h"


ADwarfGameState::ADwarfGameState(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
    State = EGameplayState::Type::Starting;
}

void ADwarfGameState::SetGameplayState(EGameplayState::Type NewState)
{
    State = NewState;
    if (DwarfGameMode)
    {
        DwarfGameMode->OnGameplayStateChange(NewState);
    }
}

void ADwarfGameState::BeginPlay()
{             
    CoinsToCollect = 0;    
    for (TActorIterator<ADwarfGold> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        CoinsToCollect++;
    }
}