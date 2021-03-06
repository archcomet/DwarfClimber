

#include "Dwarf.h"
#include "DwarfSpectatorPawn.h"


ADwarfSpectatorPawn::ADwarfSpectatorPawn(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
    // Create a camera boom attached to the root (capsule)
    CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
    CameraBoom->AttachTo(RootComponent);
    CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
    CameraBoom->TargetArmLength = 500.f;
    CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
    CameraBoom->RelativeRotation = FRotator(0.f, 180.f, 0.f);

    // Create a camera and attach to boom
    SideViewCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SideViewCamera"));
    SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
    SideViewCameraComponent->bUseControllerViewRotation = false; // We don't want the controller rotating the camera

    MovementComponent->MaxSpeed = 0.0f;
}


