
                                
#include "Dwarf.h"
#include "DwarfCharacter.h"
#include "DwarfPlayerController.h"
#include "DwarfCheckPoint.h"


ADwarfCheckPoint::ADwarfCheckPoint(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
    PointLight = PCIP.CreateDefaultSubobject<UPointLightComponent>(this, TEXT("PointLightComponent"));
    PointLight->Intensity = 1000.f;
    PointLight->bVisible = false;
    PointLight->AttachParent = RootComponent;

    bActivated = false;
}
         
void ADwarfCheckPoint::OnPickedUp(ADwarfPlayerController* DwarfController)
{
    if (bActivated)
    {
        return;
    }

    DwarfController->SetSpawnSpot(this);
    bActivated = true;

    PickupSound = NULL;

    if (PointLight)
    {
        PointLight->ToggleVisibility();
    }
}

