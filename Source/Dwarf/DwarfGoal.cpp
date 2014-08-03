

#include "Dwarf.h"
#include "DwarfPlayerController.h"
#include "DwarfGameState.h"
#include "DwarfGoal.h"


ADwarfGoal::ADwarfGoal(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void ADwarfGoal::OnPickedUp(ADwarfPlayerController* DwarfController)
{    
    DwarfController->OnReachGoal();
}


