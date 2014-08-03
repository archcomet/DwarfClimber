

#pragma once

#include "DwarfTypes.h"
#include "GameFramework/HUD.h" 
#include "DwarfHUD.generated.h"

class ADwarfGameState;

/**
 * 
 */
UCLASS()
class ADwarfHUD : public AHUD
{
	GENERATED_UCLASS_BODY()
        
    /** Font of the Menu Buttons **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=HUD)
	UFont* HUDFont;

    /** Font of the Menu Title **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=HUD)
	UFont* TitleFont;

    /** Default FontScale **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=HUD)
	float DefaultFontScale;
                           
    /** Default Button Size **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=HUD)
    FVector2D DefaultButtonSize;
                        
    /** Space between buttons **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=HUD)
    float ButtonMargin;

    /** Space betwen top of the button and top of the screen **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=HUD)
    float ButtonTop;
                            
    /** Space between top of the title and top of the screen **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=HUD)
    float TitleTop;

    /** Start Button Activation **/
    void ExecuteOnStart();
    
    /** Quit Button Activation **/
    void ExecuteOnQuit();

    /** Pause Button Activation **/
    void ExecuteOnResume();
                                           
protected:
                
    /** Mouse just clicked? **/
    bool bMouseWasClicked;

    /** Position of mouse cursor **/
    FVector2D MousePosition;
                                    
    /** Main menu buttons **/
    TArray<FHUDItem> MainMenu;
                            
    /** Pause menu buttons **/
    TArray<FHUDItem> PauseMenu;

    /** Gameover menu buttons **/
    TArray<FHUDItem> GameOverMenu;

    /** Title **/
    FHUDItem TitleItem;

    ADwarfGameState* GameState;

    /** Creates buttons **/
	virtual void PostInitializeComponents() OVERRIDE;

    /** Draws HUD and responds to mouse **/
	virtual void DrawHUD() OVERRIDE; 

    /** Adds a button to a menu **/
    FHUDItem* AddButton(TArray<FHUDItem>* Menu, FString Text);

    TArray<FHUDItem>* GetCurrentMenu();

    /** Adds title **/
    void SetTitle(FString Text);

    /** Draws an item **/
    void DrawHUDItems(FHUDItem HUDItem, float X, float Y);

    /** Calculates top left corner to center an item **/
    FORCEINLINE FVector2D GetCenteredOrign(const FVector2D& Origin, const FVector2D& Size)
    {
        return FVector2D(Origin.X - Size.X/2, Origin.Y - Size.Y/2);
    }
    
    /** Checks if mouse is inside button **/
    FORCEINLINE bool IsMouseOver(const FHUDItem HUDItem, const FVector2D& Position)
    {
        return (Position.X >= HUDItem.Origin.X - HUDItem.Size.X / 2 &&
                Position.X <= HUDItem.Origin.X + HUDItem.Size.X / 2 &&
                Position.Y >= HUDItem.Origin.Y - HUDItem.Size.Y / 2 &&
                Position.Y <= HUDItem.Origin.Y + HUDItem.Size.Y / 2);
    }
};

