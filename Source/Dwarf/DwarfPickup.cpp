

#include "Dwarf.h"
#include "DwarfCharacter.h"
#include "DwarfPlayerController.h"
#include "DwarfPickup.h"


ADwarfPickup::ADwarfPickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
    CollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADwarfPickup::OnBeginOverlap);
    RootComponent = CollisionComponent;
}

void ADwarfPickup::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ADwarfCharacter* Dwarf = Cast<ADwarfCharacter>(OtherActor);
    if (Dwarf)
    {
        ADwarfPlayerController* DwarfPlayerController = Cast<ADwarfPlayerController>(Dwarf->GetController());
        if (DwarfPlayerController)
        {
            if (PickupSound)
            {
                DwarfPlayerController->ClientPlaySound(PickupSound, 1.f, 1.f);
            }
            OnPickedUp(DwarfPlayerController);
        }
    }

}

void ADwarfPickup::OnPickedUp(ADwarfPlayerController* DwarfController)
{

}
