

#pragma once
                               
#include "Dwarf.h"
#include "DwarfHUD.h"
#include "GameFramework/PlayerController.h"
#include "DwarfPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ADwarfPlayerController : public APlayerController
{    
    typedef void (ADwarfPlayerController::*CallbackType)(void);    

	GENERATED_UCLASS_BODY()                                          

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Player)
    TSubclassOf<class APawn> DwarfCharacterClass;

    virtual void SetupInputComponent() OVERRIDE;
                                                                   
    UFUNCTION()
    void SetSpawnSpot(AActor* SpawnSpot);

    UFUNCTION()
    void Respawn();

    UFUNCTION()
    void OnReachGoal();

    void TogglePause();
                                   
protected:

    bool bSpawning;

    void OnSpawn();
                         
    void MoveRight(float Value);

    void Jump();

    void Swap();

private:

    AActor* SpawnSpot;

};
