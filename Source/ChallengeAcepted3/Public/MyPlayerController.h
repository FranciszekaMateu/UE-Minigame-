#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

// Forward declaration, para evitar la dependencia directa.
class AMyCustomHUD;

UCLASS()
class CHALLENGEACEPTED3_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    UFUNCTION()
        void OnMouseClick();

private:
    bool bIsStartScreenVisible = true;
    FText StartScreenText = FText::FromString("En un planeta muy lejano...");
    FText PlayButtonText = FText::FromString("Jugar");
};
