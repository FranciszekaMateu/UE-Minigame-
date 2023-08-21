#include "MyCustomHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"

void AMyCustomHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawStartScreen();
}

void AMyCustomHUD::DrawStartScreen()
{
	// Puedes cambiar esto con tu fuente específica si ya tienes una en tu proyecto
	UFont* Font = GEngine->GetMediumFont();

	const float ScreenCenterX = Canvas->ClipX * 0.5f;
	const float ScreenCenterY = Canvas->ClipY * 0.5f;

	// Configurar el rectángulo del botón de juego
	const float ButtonWidth = 200.0f;
	const float ButtonHeight = 100.0f;
	PlayButtonRect = FBox2D(
		FVector2D(ScreenCenterX - ButtonWidth * 0.5f, ScreenCenterY),
		FVector2D(ScreenCenterX + ButtonWidth * 0.5f, ScreenCenterY + ButtonHeight)
	);

	DrawText(
		FText::FromString(StartScreenText),
		FColor::White,
		ScreenCenterX - Font->GetStringSize(*StartScreenText) * 0.5f,
		ScreenCenterY - ButtonHeight * 1.5f,
		Font
	);

	DrawRect(FLinearColor::Blue, PlayButtonRect.Min.X, PlayButtonRect.Min.Y, ButtonWidth, ButtonHeight);

	DrawText(
		FText::FromString(PlayButtonText),
		FColor::White,
		ScreenCenterX - Font->GetStringSize(*PlayButtonText) * 0.5f,
		ScreenCenterY + ButtonHeight * 0.5f - Font->GetStringSize(*PlayButtonText) * 0.5f,
		Font
	);
}

void AMyCustomHUD::HandleStartScreenClick()
{
	// Código para manejar cuando el jugador hace clic en la pantalla de inicio. 
	// Por ejemplo, puedes revisar si el clic está dentro de PlayButtonRect y actuar en consecuencia.
}



