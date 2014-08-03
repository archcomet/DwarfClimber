

#pragma once

#include "GameFramework/Actor.h"
#include "DwarfSpike.generated.h"

/**
 * 
 */
UCLASS()
class ADwarfSpike : public AActor
{
	GENERATED_UCLASS_BODY()
                                                
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Spike)
    TSubobjectPtr<UBoxComponent> CollisionComponent;

    UFUNCTION()
    void OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
