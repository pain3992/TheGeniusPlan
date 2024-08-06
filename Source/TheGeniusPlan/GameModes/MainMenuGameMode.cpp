// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/GameModes/MainMenuGameMode.h"
#include "TheGeniusPlan/GameModes/MainMenuHUD.h"
#include "TheGeniusPlan/Characters/MainMenuPawn.h"
#include "TheGeniusPlan/GameModes/MainMenuPlayerController.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	HUDClass = AMainMenuHUD::StaticClass();
	DefaultPawnClass = AMainMenuPawn::StaticClass();
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
}
