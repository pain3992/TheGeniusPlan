// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheGeniusPlanGameMode.h"
#include "TheGeniusPlanCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheGeniusPlanGameMode::ATheGeniusPlanGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
