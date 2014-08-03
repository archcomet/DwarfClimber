

#pragma once

#include "DwarfPickup.h"
#include "DwarfGoal.generated.h"

/**
 * 
 */
UCLASS()
class ADwarfGoal : public ADwarfPickup
{
	GENERATED_UCLASS_BODY()

    void OnPickedUp(ADwarfPlayerController* DwarfController) OVERRIDE;
	
	
};
