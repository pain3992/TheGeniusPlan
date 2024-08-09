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

    // 게임 상태 및 플레이어 상태를 가져옵니다.
    if (AMainHallPlayerState* PlayerState = NewPlayer->GetPlayerState<AMainHallPlayerState>())
    {
        // 플레이어 컨트롤러의 이름을 PlayerState에 설정합니다.
        PlayerState->PlayerName = NewPlayer->GetName();

        // 기본 점수를 0으로 설정합니다.
        PlayerState->SetPlayerScore(0);

        UE_LOG(LogTemp, Log, TEXT("Client has joined the game. PlayerController name: %s, PlayerState name: %s"),
            *NewPlayer->GetName(), *PlayerState->PlayerName);
    }

    // 플레이어 상태 업데이트
    if (AMainHallGameState* CurrentGameState = GetWorld()->GetGameState<AMainHallGameState>())
    {
        CurrentGameState->UpdatePlayerRankings();
    }
}

void AMainHallGameMode::Logout(AController* Exiting)
{
	//Super::Logout(Exiting);
	//// Ensure the GameState is valid and update player rankings
	//if (AMainHallGameState* LocalGameState = GetGameState<AMainHallGameState>())
	//{
	//	LocalGameState->UpdatePlayerRankings();
	//}
}
