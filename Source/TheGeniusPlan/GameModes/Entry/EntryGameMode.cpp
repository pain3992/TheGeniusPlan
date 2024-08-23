// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/GameModes/Entry/EntryGameMode.h"
#include "TheGeniusPlan/Characters/EntryPawn.h"
#include "TheGeniusPlan/HUD/EntryHUD.h"
#include "TheGeniusPlan/Player/EntryPlayerController.h"

AEntryGameMode::AEntryGameMode()
{
	HUDClass = AEntryHUD::StaticClass();
	DefaultPawnClass = AEntryPawn::StaticClass();
	PlayerControllerClass = AEntryPlayerController::StaticClass();
}
