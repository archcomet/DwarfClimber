

#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "DwarfSpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class ADwarfSpectatorPawn : public ASpectatorPawn
{
	GENERATED_UCLASS_BODY()

    /** Side view camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    TSubobjectPtr<UCameraComponent> SideViewCameraComponent;

    /** Camera boom positioning the camera beside the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    TSubobjectPtr<class USpringArmComponent> CameraBoom;
	
	
};
