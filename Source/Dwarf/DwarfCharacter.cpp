

#include "Dwarf.h"
#include "DwarfFlag.h"
#include "DwarfPlayerController.h"
#include "DwarfCharacter.h"


ADwarfCharacter::ADwarfCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
    // Set size for collision capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUseControllerViewRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Face in the direction we are moving..
	CharacterMovement->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	CharacterMovement->GravityScale = 2.f;
	CharacterMovement->AirControl = 0.80f;
	CharacterMovement->JumpZVelocity = 1000.f;
	CharacterMovement->GroundFriction = 3.f;
	CharacterMovement->MaxWalkSpeed = 600.f;
	CharacterMovement->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

    bRespondsToInput = true;
}

void ADwarfCharacter::MoveRight(float Value)
{
    if (bRespondsToInput)
    {
        AddMovementInput(FVector(0.f,-1.f,0.f), Value);
    }
}

void ADwarfCharacter::Jump()
{
	if (bRespondsToInput)
    {
        ACharacter::Jump();
    }
}

void ADwarfCharacter::Die()
{
	if ( bIsDying										// already dying
		|| IsPendingKill()								// already destroyed
		|| GetWorld()->GetAuthGameMode() == NULL
		|| GetWorld()->GetAuthGameMode()->GetMatchState() == MatchState::LeavingMap)	// level transition occurring
	{
		return;
	}       
    
	bIsDying = true;
    bRespondsToInput = false;

    float DeathAnimDuration = 0.f;               
    if (DeathAnim)
	{
		DeathAnimDuration = PlayAnimMontage(DeathAnim);
        DeathAnimDuration /= (Mesh.IsValid() && Mesh->GlobalAnimRateScale > 0) ? Mesh->GlobalAnimRateScale : 1; 
	}

	GetWorldTimerManager().SetTimer(this, &ADwarfCharacter::OnDieAnimationEnd, DeathAnimDuration + 0.1, false);
}

void ADwarfCharacter::OnDieAnimationEnd()
{
    Mesh->GlobalAnimRateScale = 0.0;

    ADwarfPlayerController* PlayerController = Cast<ADwarfPlayerController>(Controller);
    if (PlayerController)
    {
        PlayerController->Respawn();
    }
}

void ADwarfCharacter::BeginPlay()
{
    if (FlagClass) {

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = Instigator;

        Flag = GetWorld()->SpawnActor<ADwarfFlag>(FlagClass, GetActorLocation(), GetActorRotation(), SpawnParams);
        Flag->AttachRootComponentTo(Mesh, TEXT("DualWeaponPoint"), EAttachLocation::SnapToTarget);
    }
}

void ADwarfCharacter::OnReachGoal()
{
    bRespondsToInput = false;
}
