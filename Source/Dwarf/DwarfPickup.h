

#pragma once

#include "GameFramework/Pawn.h"
#include "DwarfPickup.generated.h"

class ADwarfPlayerController;
/**
 * 
 */
UCLASS()
class ADwarfPickup : public APawn
{
	GENERATED_UCLASS_BODY()

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
    TSubobjectPtr<USphereComponent> CollisionComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Pickup)
    USoundCue* PickupSound;

    UFUNCTION()
    void OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    virtual void OnPickedUp(ADwarfPlayerController* DwarfController);
};
