#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyPlayerController.h" // Incluir para resolver el error C2027
#include "MyCustomHUD.generated.h"

UCLASS()
class CHALLENGEACEPTED3_API AMyCustomHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Start Screen")
		FString StartScreenText = "Start Screen Text";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Start Screen")
		FString PlayButtonText = "Play";

	void HandleStartScreenClick();

private:
	FBox2D PlayButtonRect;

	void DrawStartScreen();
};

