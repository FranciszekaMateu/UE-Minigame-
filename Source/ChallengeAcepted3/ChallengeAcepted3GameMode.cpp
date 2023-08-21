// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChallengeAcepted3GameMode.h"
#include "ChallengeAcepted3Character.h"
#include "MyCustomHUD.h"
#include "MyPlayerController.h"

#include "UObject/ConstructorHelpers.h"

AChallengeAcepted3GameMode::AChallengeAcepted3GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = AMyCustomHUD::StaticClass();
}
