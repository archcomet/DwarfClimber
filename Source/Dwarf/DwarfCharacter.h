

#pragma once

#include "GameFramework/Character.h"
#include "DwarfCharacter.generated.h"


class ADwarfFlag;

/**
 * 
 */
UCLASS()
class ADwarfCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()
    
    /** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<UCameraComponent> SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

    UPROPERTY(EditDefaultsOnly, Category=Flag)
    TSubclassOf<class ADwarfFlag> FlagClass;

    ADwarfFlag* Flag;

    /** melee anim */
	UPROPERTY(EditDefaultsOnly, Category=Pawn)
	UAnimMontage* MeleeAnim;

	/** death anim */
	UPROPERTY(EditDefaultsOnly, Category=Pawn)
	UAnimMontage* DeathAnim;

    UFUNCTION()
    void OnDieAnimationEnd();

    UFUNCTION()
    void OnReachGoal();

    UFUNCTION()        
    void MoveRight(float Value);
                   
    UFUNCTION()
    void Die();  

    virtual void BeginPlay() OVERRIDE;

    virtual void Jump() OVERRIDE;

private:

    bool bIsDying;

    bool bRespondsToInput;

};
