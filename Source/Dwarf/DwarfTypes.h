
#pragma once

#include "DwarfTypes.generated.h"

UENUM()
namespace EGameplayState
{
    enum Type {
        Starting,
        Playing,
        Finished
    };
}

USTRUCT()
struct FHUDItem
{
    GENERATED_USTRUCT_BODY()

    DECLARE_DELEGATE(FCallback);

    /** On Click Callback  **/
    FCallback Callback;

    // Layout      

    /** Center Origin **/
    FVector2D Origin;

    /** Size of item **/
    FVector2D Size;

    // Text

    /** Text value **/
    FText Text;

    /** Text Font **/
    UFont* Font;

    /** Text Color **/
    FLinearColor TextColor;

    /** Text Outline Color **/
    FLinearColor OutlineColor;

    /** Text Shadow Color **/
    FLinearColor ShadowColor;

    /** Text Scale **/
    float TextScale;

    // Background

    /** Background Color **/
    FLinearColor BackgroundColor;

    /** Background Hover Color **/
    FLinearColor HoverColor;

    //default properties

    FHUDItem()
    {
        // Layout         
        Size.X = 200.f;
        Size.Y = 50.f;

        // Text
        TextColor = FLinearColor(1.f, 1.f, 1.f, 1.f);
        OutlineColor = FLinearColor(0.f, 0.f, 0.f, 1.f);
        ShadowColor = FLinearColor(0.f, 0.f, 0.f, 0.0f);
        TextScale = 1.f;

        // Rect
        BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.5f);
        HoverColor = FLinearColor(0.3f, 0.3f, 0.f, 0.5f);
    }

    FHUDItem(FText InText) : FHUDItem()
    {
        Text = InText;
    }
};