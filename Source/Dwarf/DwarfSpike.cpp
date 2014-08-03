
                                  
#include "Dwarf.h"
#include "DwarfCharacter.h"
#include "DwarfSpike.h"


ADwarfSpike::ADwarfSpike(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
    CollisionComponent = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BaseBoxComponent"));
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADwarfSpike::OnBeginOverlap);
    RootComponent = CollisionComponent;
}
              

void ADwarfSpike::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ADwarfCharacter* Dwarf = Cast<ADwarfCharacter>(OtherActor);
    if (Dwarf)
    {
        Dwarf->Die();
    }
}
