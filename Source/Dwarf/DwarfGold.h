

#pragma once

#include "DwarfPickup.h"
#include "DwarfGold.generated.h"

class ADwarfPlayerController;
/**
 * 
 */
UCLASS()
class ADwarfGold : public ADwarfPickup
{
	GENERATED_UCLASS_BODY()

    bool bCollected;

    void OnPickedUp(ADwarfPlayerController* DwarfController) OVERRIDE;
	
};
