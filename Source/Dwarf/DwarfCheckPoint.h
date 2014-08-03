

#pragma once

#include "GameFramework/Actor.h"
#include "DwarfPickup.h"
#include "DwarfCheckPoint.generated.h"

/**
 * 
 */
UCLASS()
class ADwarfCheckPoint : public ADwarfPickup
{
	GENERATED_UCLASS_BODY()
	                                                                 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Checkpoint)
    TSubobjectPtr<UPointLightComponent> PointLight;

    void OnPickedUp(ADwarfPlayerController* DwarfController) OVERRIDE;

private:
    
    bool bActivated;

};

