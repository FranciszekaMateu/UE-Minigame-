#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"



void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Cargar y mostrar el widget de inicio
    if (StartScreenWidgetClass)
    {
        StartScreenWidget = CreateWidget<UUserWidget>(this, StartScreenWidgetClass);
        if (StartScreenWidget)
        {
            StartScreenWidget->AddToViewport();
        }
    }
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("LeftClick", IE_Pressed, this, &AMyPlayerController::OnMouseClick);
}

void AMyPlayerController::OnMouseClick()
{
    AMyCustomHUD* CustomHUD = Cast<AMyCustomHUD>(GetHUD());
    if (CustomHUD)
    {
        CustomHUD->HandleStartScreenClick();
    }
}
