// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFGameState.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "TheGeniusPlan/Actor/AAFLandLoction.h"
#include "TheGeniusPlan/GameModes/GeniusGameInstance.h"
#include "TheGeniusPlan/Widget/MainGame/MainGameWidget.h"

AAAFGameState::AAAFGameState()
{
	StageCount = 0;
	GameStep = EGameStep::None;
}

void AAAFGameState::SetGameStep(EGameStep NewStep)
{
	GameStep = NewStep;
	UE_LOG(LogTemp, Error, TEXT("Game Step New Step : %d"), NewStep);

	switch (NewStep)
	{
	case EGameStep::None:
		break;
	case EGameStep::RoundStart:

		break;
	case EGameStep::RoundEnd:
		RequestWinnerCheck();
		RequestGameStepEnd();
		//if(StageCount < 1)
		//{
		//	StageCount++;
		//	RequestWinnerCheck();
		//	RequestGameStepReset();
		//}
		//else
		//{
		//	RequestGameStepEnd();
		//}
		break;
	case EGameStep::GameEnd:
		break;
	default:
		break;
	}
}

EGameStep AAAFGameState::GetGameStep()
{
	return GameStep;
}

void AAAFGameState::BeginPlay()
{
	Super::BeginPlay();
	RequestSetPlayerLocation();
}

void AAAFGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(AAAFGameState, PlayerLocations);
	DOREPLIFETIME(AAAFGameState, GameStep);
}

void AAAFGameState::RequestGameStepReset()
{
	UE_LOG(LogTemp, Error, TEXT("RequestGameStepReset"));
	ResponseGameStepReset();
}

void AAAFGameState::RequestSetPlayerLocation()
{
	UE_LOG(LogTemp, Error, TEXT("RequestSetPlayerLocation"));
	ResponseSetPlayerLocation();
}

void AAAFGameState::ResponseGameStepReset_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("ResponseGameStepReset"));
	ResponseSetPlayerLocation();
}

void AAAFGameState::RequestGameStepEnd()
{
	UE_LOG(LogTemp, Error, TEXT("RequestGameStepEnd"));
	ResponseGameStepEnd();
}

void AAAFGameState::RequestWinnerCheck()
{
	ResponsetWinnerCheck();
}

void AAAFGameState::ResponsetWinnerCheck_Implementation()
{
	for (auto Client : PlayerArray)
	{

		if (Client->GetOwningController() && Client->GetOwningController()->GetPawn())
		{
			AAAFPlayerState* CastPlayerState = Cast<AAAFPlayerState>(Client->GetOwningController()->PlayerState);

			if (CastPlayerState->Lose == true)
			{
				continue;
			}

			CastPlayerState->win += 1;

		}
	}
}

void AAAFGameState::ResponseGameStepEnd_Implementation()
{
	int i = 0;
	APlayerController* Winner = nullptr;
	uint8 WinCount = 0;


	UGeniusGameInstance* GameInstance = Cast<UGeniusGameInstance>(GetGameInstance());

	for (auto Client : PlayerArray)
	{

		if (Client->GetOwningController() && Client->GetOwningController()->GetPawn())
		{
			AAAFPlayerState* CastPlayerState = Cast<AAAFPlayerState>(Client->GetOwningController()->PlayerState);

			if (CastPlayerState || GameInstance)
			{
				if ((CastPlayerState->win) > WinCount)
				{
					Winner = CastPlayerState->GetPlayerController();
				}
			}
		}
	}

	AGeniusPlayerState* PS = Cast<AGeniusPlayerState>(Winner->PlayerState);
	PS->Score += 10;
	PS->GarnetCount += 10;


	FPlayerScoreData ScoreData;
	ScoreData.PlayerName = PS->GetPlayerName();
	ScoreData.Score = PS->GetScore();
	ScoreData.GarnetCount = PS->GetGarnetCount();
	GameInstance->SavedPlayerScores.Add(ScoreData);

	//FPlayerScoreData ScoreData;
	//ScoreData.PlayerName = Winner->PlayerState->GetPlayerName();
	//ScoreData.Score = 10;
	//ScoreData.GarnetCount = 10;
	//uint8 Check = 0;

	//for (auto PlayersName : GameInstance->SavedPlayerScores)
	//{
	//	if(PlayersName.PlayerName == Winner->PlayerState->GetPlayerName())
	//	{
	//		PlayersName.Score += 10;
	//		PlayersName.GarnetCount += 10;
	//		Check = 1;
	//	}
	//}

	//if (Check == 0)
	//{
	//	GameInstance->SavedPlayerScores.Add(ScoreData);
	//}

	FString TravelURL = FString::Printf(TEXT("/Game/Levels/MainLevel?game=/Script/TheGeniusPlan.MainGameModeBase"));
	GetWorld()->ServerTravel(TravelURL);
}

void AAAFGameState::OnReq_GameStepChange()
{
	if (EventDisptacherGameStepChange.IsBound())
	{
		EventDisptacherGameStepChange.Broadcast(GameStep);
	}
}

void AAAFGameState::ResponseSetPlayerLocation_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("ResponseSetPlayerLocation"));
	if (PlayerArray.Num() > 1)
	{

		TArray<AActor*> PlayerLocation;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAAFLandLoction::StaticClass(), PlayerLocation);

		for (auto Start : PlayerLocation)
		{
			PlayerLocations.Add(Start->GetActorLocation());
		}

		GetWorld()->GetTimerManager().ClearTimer(GameModeThirdHandle);
		GetWorld()->GetTimerManager().SetTimer(GameModeFHandle, this, &AAAFGameState::ResponseSendLocationByClient, 15.0f, false);

	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(GameModeThirdHandle, this, &AAAFGameState::ResponseSetPlayerLocation, 0.1f, false);
	}
}

void AAAFGameState::ResponseSendLocationByClient_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("ResponseSendLocationByClient"));
	if (PlayerLocations.Num() > 1)
	{
		int i = 0;

		for (auto Client : PlayerArray)
		{
			FVector NewLocation = PlayerLocations[i];

			if (Client->GetOwningController() && Client->GetOwningController()->GetPawn())
			{
				AAAFPlayerState* CastPlayerState = Cast<AAAFPlayerState>(Client->GetOwningController()->PlayerState);
				CastPlayerState->Location = NewLocation;
			}

			++i;

		}

		GetWorld()->GetTimerManager().SetTimer(GameModeFiveHandle, this, &AAAFGameState::ChangeGameStepByRound, 15.0f, false);

	}

}

void AAAFGameState::ChangeGameStepByRound_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("ChangeGameStepByRound"));
	GameStep = EGameStep::RoundStart;
}
