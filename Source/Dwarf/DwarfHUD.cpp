

#include "Dwarf.h"
#include "DwarfGameState.h"
#include "DwarfPlayerController.h"
#include "DwarfHUD.h"


ADwarfHUD::ADwarfHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{                              
    // Default Button Style

    DefaultFontScale = 1.f;
    DefaultButtonSize.X = 200.f;
    DefaultButtonSize.Y = 50.f;
    
    // Initial Layout

    ButtonMargin = 10.f;
    TitleTop = 150.f;
    ButtonTop = 300.f;
}

void ADwarfHUD::PostInitializeComponents()
{
    Super::PostInitializeComponents();     

    // Create title

    SetTitle(TEXT("DWARF CLIMBER!"));

    // Create Main Menu

    AddButton(&MainMenu, TEXT("Start"))->Callback.BindUObject(this, &ADwarfHUD::ExecuteOnStart);
    AddButton(&MainMenu, TEXT("Quit"))->Callback.BindUObject(this, &ADwarfHUD::ExecuteOnQuit);
    
    // Create Pause Menu

    AddButton(&PauseMenu, TEXT("Resume"))->Callback.BindUObject(this, &ADwarfHUD::ExecuteOnResume);
    AddButton(&PauseMenu, TEXT("Quit"))->Callback.BindUObject(this, &ADwarfHUD::ExecuteOnQuit);

    // Set Game Over Menu to Current

    AddButton(&GameOverMenu, TEXT("Quit"))->Callback.BindUObject(this, &ADwarfHUD::ExecuteOnQuit);

    GameState = GetWorld()->GetGameState<ADwarfGameState>();
}         

void ADwarfHUD::SetTitle(FString Text)
{
    TitleItem.Text = FText::FromString(Text);
    TitleItem.BackgroundColor.A = 0.f;
    TitleItem.HoverColor.A = 0.f;
    TitleItem.ShadowColor.A = 0.7f;
    TitleItem.Font = TitleFont;
}

FHUDItem* ADwarfHUD::AddButton(TArray<FHUDItem>* Menu, FString Text)
{
    FHUDItem Button = FHUDItem(FText::FromString(Text));
    Button.Size = DefaultButtonSize;
    Button.Font = HUDFont;
    Menu->Add(Button);
    return &Menu->Last();
}

TArray<FHUDItem>* ADwarfHUD::GetCurrentMenu()
{
    TArray<FHUDItem>* CurrentMenu = NULL;
    
    switch (GameState->State)
    {

    case EGameplayState::Type::Starting:
        CurrentMenu = &MainMenu;
        break;

    case EGameplayState::Type::Playing:
        CurrentMenu = GetOwningPlayerController()->IsPaused() ? &PauseMenu : NULL;      
        break;

    case EGameplayState::Type::Finished:
        {
            SetTitle(TEXT("You've reached the summit!"));
            CurrentMenu = &GameOverMenu;     
        }
        break;
    }

    return CurrentMenu;
}

void ADwarfHUD::DrawHUD()
{
    Super::DrawHUD();                         

    TArray<FHUDItem>* CurrentMenu = GetCurrentMenu();


    if (GameState->State != EGameplayState::Starting)
    {

        FString PowerLevelString = FString::Printf(TEXT("Gold: %2i/%i"), GameState->CoinsCollected, GameState->CoinsToCollect);
        DrawText(PowerLevelString, FColor::White, 50, 50, HUDFont);
    }

    if (CurrentMenu)
    {
        APlayerController* PlayerController = GetOwningPlayerController();
        PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
        bMouseWasClicked = PlayerController->WasInputKeyJustPressed(EKeys::LeftMouseButton);

        // Get menu position

        float ScreenCenter = Canvas->SizeX / 2.f;
        float ButtonY = ButtonTop;       

        if (GameState->State == EGameplayState::Finished)
        {
            ButtonY += 300.f;
        }

        // Draw Title

        DrawHUDItems(TitleItem, ScreenCenter, TitleTop);

        // Draw current menu

        for (auto HUDButton : *CurrentMenu)
        {
            DrawHUDItems(HUDButton, ScreenCenter, ButtonY);
            ButtonY += HUDButton.Size.Y + ButtonMargin;
        }
    }
}

void ADwarfHUD::DrawHUDItems(FHUDItem HUDItem, float X, float Y)
{                                               
    // Get offsets
    HUDItem.Origin.X = X;
    HUDItem.Origin.Y = Y;

    float TextWidth;
    float TextHeight;

    GetTextSize(
		HUDItem.Text.ToString(), 
		TextWidth, 
		TextHeight, 
		HUDItem.Font,             
        HUDItem.TextScale
	);
     
    // Check mouse position

    bool bMouseOver = IsMouseOver(HUDItem, MousePosition);

    // Draw Rectangle

    FCanvasTileItem RectItem( 
        GetCenteredOrign(HUDItem.Origin, HUDItem.Size), 
		HUDItem.Size, 
		bMouseOver ?  HUDItem.HoverColor : HUDItem.BackgroundColor
	);
                 
    RectItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(RectItem);
 
    // Draw Text

	FCanvasTextItem TextItem (
		GetCenteredOrign(HUDItem.Origin, FVector2D(TextWidth, TextHeight)),
        HUDItem.Text,
		HUDItem.Font,
		HUDItem.TextColor
	);
 
	TextItem.Scale.Set(HUDItem.TextScale, HUDItem.TextScale); 
	TextItem.bOutlined = HUDItem.OutlineColor.A != 0.f;
    TextItem.OutlineColor = HUDItem.OutlineColor;

    if (HUDItem.ShadowColor.A != 0)
    {
        TextItem.EnableShadow(HUDItem.ShadowColor, FVector2D(5.f, 5.f));
    }    

	Canvas->DrawItem(TextItem);

    // Activate button

    if (bMouseOver && bMouseWasClicked)
    {
        HUDItem.Callback.ExecuteIfBound();
    }
}
                  
void ADwarfHUD::ExecuteOnStart()
{
    GetOwningPlayerController()->bShowMouseCursor = false;
    GetWorld()->GetGameState<ADwarfGameState>()->SetGameplayState(EGameplayState::Type::Playing);
}

void ADwarfHUD::ExecuteOnQuit()
{
    GetOwningPlayerController()->ConsoleCommand("quit");
}

void ADwarfHUD::ExecuteOnResume()
{
    ADwarfPlayerController* DwarfController = Cast<ADwarfPlayerController>(GetOwningPlayerController());
    DwarfController->TogglePause();
}
