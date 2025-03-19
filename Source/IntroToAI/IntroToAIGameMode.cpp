// Copyright Epic Games, Inc. All Rights Reserved.

#include "IntroToAIGameMode.h"
#include "IntroToAICharacter.h"
#include "UObject/ConstructorHelpers.h"

AIntroToAIGameMode::AIntroToAIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
