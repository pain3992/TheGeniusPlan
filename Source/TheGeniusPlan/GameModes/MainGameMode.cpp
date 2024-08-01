// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/GameModes/MainGameMode.h"

AMainGameMode::AMainGameMode()
{
	// DefaultPawnClass = ALobbyGameMode::StaticClass();
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
