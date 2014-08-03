
                              
#include "Dwarf.h"
#include "DwarfGameState.h"
#include "DwarfCharacter.h"
#include "DwarfPlayerController.h"


ADwarfPlayerController::ADwarfPlayerController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
    SetCinematicMode(true, true, true);
    bShowMouseCursor = true;
}                          

void ADwarfPlayerController::SetSpawnSpot(AActor* NewSpawnSpot)
{
    SpawnSpot = NewSpawnSpot;
}

void ADwarfPlayerController::Respawn()
{
    // Remove current character
    APawn* PreviousPawn = GetPawn();
    if (PreviousPawn)
    {
        UnPossess();
        PreviousPawn->SetActorHiddenInGame(true);
        PreviousPawn->SetLifeSpan(0.1f);
    }
    
    if (DwarfCharacterClass != NULL && SpawnSpot != NULL)
    {
        bSpawning = true;

        FVector SpawnLocation = SpawnSpot->GetActorLocation();
        FRotator SpawnRotation = SpawnSpot->GetActorRotation();  
                  
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = Instigator;

        ADwarfCharacter* DwarfCharacter= GetWorld()->SpawnActor<ADwarfCharacter>(DwarfCharacterClass, SpawnLocation, SpawnRotation, SpawnParams);                      

        GetWorldTimerManager().SetTimer(this, &ADwarfPlayerController::OnSpawn, 0.1f, false);
        Possess(DwarfCharacter);
    }
}

void ADwarfPlayerController::OnSpawn()
{
    bSpawning = false;
}

void ADwarfPlayerController::SetupInputComponent()
{
    APlayerController::SetupInputComponent();
  
	InputComponent->BindAxis("MoveRight", this, &ADwarfPlayerController::MoveRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ADwarfPlayerController::Jump);
    
    FInputActionBinding& TogglePause = InputComponent->BindAction("Pause", IE_Pressed, this, &ADwarfPlayerController::TogglePause);
    TogglePause.bExecuteWhenPaused = true;
}     

void ADwarfPlayerController::MoveRight(float Value)
{
    if (!bSpawning)
    {
        ADwarfCharacter* Character = Cast<ADwarfCharacter>(GetPawn());
        if (Character != NULL)
        {
            Character->MoveRight(Value);
        }
    }
}


void ADwarfPlayerController::Jump()
{
    if (!bSpawning)
    {
        ADwarfCharacter* Character = Cast<ADwarfCharacter>(GetPawn());
        if (Character != NULL)
        {
            Character->Jump();
        }
    }
}

void ADwarfPlayerController::TogglePause()
{
    bool toggleOn = !IsPaused();

    bShowMouseCursor = toggleOn;
    SetPause(toggleOn);   
    Cast<ULocalPlayer>(Player)->ViewportClient->SetSuppressTransitionMessage(toggleOn);
}

void ADwarfPlayerController::OnReachGoal()
{
    ADwarfGameState* DwarfGameState = GetWorld()->GetGameState<ADwarfGameState>();
    DwarfGameState->SetGameplayState(EGameplayState::Type::Finished);

    ADwarfCharacter* DwarfCharacter = Cast<ADwarfCharacter>(GetPawn());
    DwarfCharacter->OnReachGoal();
    bShowMouseCursor = true;
}
