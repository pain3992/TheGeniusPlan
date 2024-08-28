// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/GameModes/MainGameModeBase.h"

#include "MainGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "MainGame/GyulhapGameMode.h"
#include "MainGame/OpenPassGameMode.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "TheGeniusPlan/Player/GeniusPlayerController.h"
#include "TheGeniusPlan/Player/GeniusPlayerState.h"
#include "TheGeniusPlan/GameModes/MainGame/AAFGameModeBase.h"
#include "TheGeniusPlan/Player/MainHallPlayerController.h"
#include "TheGeniusPlan/TheGeniusPlanCharacter.h"

AMainGameModeBase::AMainGameModeBase()
{
	// TODO: 수정 예정, 토탈라운드와 위닝스코어 검토
	TotalRound = 5;
	CurrentRound = 0;
	WinningScore = 10;

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C'"));

	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HUDClass = AMainGameHUD::StaticClass();
	GameStateClass = AMainGameStateBase::StaticClass();
	PlayerStateClass = AGeniusPlayerState::StaticClass();
	PlayerControllerClass = AMainHallPlayerController::StaticClass();

	// 카운트다운 시간 (테스트 후 다른 시간으로 변경)
	CountdownTimeInSeconds = 300;
}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// TEST: 메인 게임모드 시작시, 메인매치 게임 등록 (결합게임 모드, 오픈패스 게임 모드)
	if (PossibleGameModes.Num() == 0)
	{
		PossibleGameModes.Add(AGyulhapGameMode::StaticClass());
		PossibleGameModes.Add(AAAFGameModeBase::StaticClass());
	}
	// 게임 시작

	GetWorld()->GetTimerManager().SetTimer(GameModeHandle, this, &AMainGameModeBase::SelectNextGameMode, 10.0f, false);
}

void AMainGameModeBase::HandleGameStart()
{
	// 플레이어 점수 및 기타 필요한 데이터 초기화
	// for (int32 PlayerID : PlayingPlayers)
	// {
	// 	PlayerScores.Add(PlayerID, 0);
	// }
	// 첫번째 라운드 시작
	TransitionToNextRound();
}

void AMainGameModeBase::TransitionToNextRound()
{
	if (CurrentRound < TotalRound)
	{
		// 라운드수 적용
		CurrentRound++;
		// 라운드 규칙 적용
		SetGameRules();
	}
	{
		/**
		 * CASE: FinalGameMode 적용시 FinalGameMode 변경
		 * CASE: FinalGameMode 미적용시 EndGame 호출
		 */
	}
}

void AMainGameModeBase::HandleRoundEnd()
{
	// 라운드 종료를 초리하는 로직
	// 라운드 승자를 결정하고 승자
	// NOTE: 승자가 1명이 아니고 여러명일 수 있으므로 플레이어ID를 리스트로 받아야함
	// int32 WinningPlayerId = 승자결정함수 호출
	TArray<int32> Winners;
	Winners.Push(1);
	Winners.Push(2);
	Winners.Push(3);

	// 승자를 받아와서 점수 반영
	// for ()

	// 누가 게임의 승자인지 체크
}

void AMainGameModeBase::CheckRoundWinner()
{
	for (const auto& PlayerScore : PlayerScores)
	{
		if (PlayerScore.Value >= WinningScore)
		{
			EndGame(PlayerScore.Key);
			return;
		}
	}
	// 아무도 승리하지 않았다면 다음으로 이동
	TransitionToNextRound();
}

void AMainGameModeBase::EndGame(int32 WinningPlayerId)
{
	// 게임 종료후 로직 처리
	// UI 표기, 결과 저장 등등
}

void AMainGameModeBase::SetGameRules()
{
	// 게임 규칙 정의
	// 특정 조건, 아이템 스폰 등등
}

void AMainGameModeBase::SetCountdownRule()
{
	if (AMainGameStateBase* MainGameState = GetGameState<AMainGameStateBase>())
	{
		MainGameState->StartCountdown(CountdownTimeInSeconds);
	}
}

void AMainGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (AMainGameStateBase* MainGameState = GetGameState<AMainGameStateBase>())
	{
		if (AGeniusPlayerState* NewPlayerState = NewPlayer->GetPlayerState<AGeniusPlayerState>())
		{
			MainGameState->AddPlayer(NewPlayerState);
			// 플레이어 컨트롤러의 이름을 PlayerState에 설정합니다.
			NewPlayerState->PlayerName = NewPlayer->GetName();

			// 기본 점수를 0으로 설정합니다.
			NewPlayerState->SetPlayerScore(0);
		}
	}
}

void AMainGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (APlayerController* PlayerController = Cast<AGeniusPlayerController>(Exiting))
	{
		if (AMainGameStateBase* MainGameState = GetGameState<AMainGameStateBase>())
		{
			MainGameState->RemovePlayer(PlayerController->GetPlayerState<AGeniusPlayerState>());
		}
	}
}

/**
 * @description
 */
void AMainGameModeBase::SelectNextGameMode()
{
	/**
	 * 1. 매인매치 게임모드 있을경우
	 */
	if (PossibleGameModes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, PossibleGameModes.Num() - 1);
		TSubclassOf<AGameMode> SelectedGameMode = PossibleGameModes[RandomIndex];
		PossibleGameModes.Remove(SelectedGameMode);

		FString LevelName;

		if(SelectedGameMode == AAAFGameModeBase::StaticClass())
		{
			LevelName = TEXT("AAFLevel");
		}
		else if(SelectedGameMode == AGyulhapGameMode::StaticClass())
		{
			LevelName = TEXT("GyulhapLevel");
		}

		FString TravelURL = FString::Printf(TEXT("/Game/Levels/%s?game=/Script/TheGeniusPlan.%s"), *LevelName,*SelectedGameMode->GetName());
		GetWorld()->ServerTravel(TravelURL);
	}
}

// void AMainGameModeBase::TransitionToNextRound()
// {
// }
//
// void AMainGameModeBase::HandleRoundEnd()
// {
// }
//
// void AMainGameModeBase::CheckForOverallWinner()
// {
// }
//
//
// void AMainGameModeBase::EndMatch(int32 WinningPlayerId)
// {
// }
