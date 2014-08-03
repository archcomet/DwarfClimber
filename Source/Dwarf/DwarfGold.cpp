

#include "Dwarf.h"
#include "DwarfGameState.h"
#include "DwarfGold.h"


ADwarfGold::ADwarfGold(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
    bCollected = false;
}

void ADwarfGold::OnPickedUp(ADwarfPlayerController* DwarfController)
{
    if (bCollected)
    {
        return;
    }

    ADwarfGameState* DwarfGameState = GetWorld()->GetGameState<ADwarfGameState>();
    DwarfGameState->CoinsCollected++;
    SetActorHiddenInGame(true);
    SetLifeSpan(0.1f);
    bCollected = true;
}


