// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/GameModes/MainHallGameMode.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerController.h"
#include "TheGeniusPlan/TheGeniusPlanCharacter.h"
#include "TheGeniusPlan/Widget/MainHallUserWidget.h"
#include "TheGeniusPlan/PlayerState/MainHallPlayerState.h"
#include "TheGeniusPlan/GameState/MainHallGameState.h"
#include "TheGeniusPlan/HUD/MainHallHUD.h"


AMainHallGameMode::AMainHallGameMode()
{
	DefaultPawnClass = ATheGeniusPlanCharacter::StaticClass();
	HUDClass = AMainHallHUD::StaticClass();
	GameStateClass = AMainHallGameState::StaticClass();
	PlayerStateClass = AMainHallPlayerState::StaticClass();
}

void AMainHallGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// Ensure the GameState is valid and update player rankings
	// if (AMainHallGameState* GameState = GetGameState<AMainHallGameState>())
	// {
	// 	GameState->UpdatePlayerRankings();
	// }
}

void AMainHallGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	// Ensure the GameState is valid and update player rankings
	// if (AMainHallGameState* GameState = GetGameState<AMainHallGameState>())
	// {
	//	GameState->UpdatePlayerRankings();
	// }
}
