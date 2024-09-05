// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFGameState.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "Net/UnrealNetwork.h"
#include "TheGeniusPlan/Player/GeniusPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TheGeniusPlan/Actor/AAFLandLoction.h"
#include "TheGeniusPlan/GameModes/GeniusGameInstance.h"

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
		if(StageCount < 3)
		{
			StageCount++;
			RequestWinnerCheck();
			RequestGameStepReset();
		}
		else
		{
			RequestGameStepEnd();
		}
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

			if(CastPlayerState->Lose == true)
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

	for (auto Client : PlayerArray)
	{

		if (Client->GetOwningController() && Client->GetOwningController()->GetPawn())
		{
			AAAFPlayerState* CastPlayerState = Cast<AAAFPlayerState>(Client->GetOwningController()->PlayerState);

			if(CastPlayerState->win > WinCount)
			{
				Winner = CastPlayerState->GetPlayerController();
				WinCount = CastPlayerState->win;
			}
		}

		++i;

	}

	UGeniusGameInstance* GameInstance = Cast<UGeniusGameInstance>(GetGameInstance());
	GameInstance->PreGameWinner = Winner;

	UE_LOG(LogTemp, Error, TEXT("ResponseGameStepEnd"));
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
