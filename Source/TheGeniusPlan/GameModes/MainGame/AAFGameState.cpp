// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFGameState.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "Net/UnrealNetwork.h"
#include "TheGeniusPlan/Player/GeniusPlayerController.h"

AAAFGameState::AAAFGameState()
{
	StageCount = 0;
	GameStep = EGameStep::None;
	AbundanceLand = 0;
	FamineLand = 0;
}

void AAAFGameState::SetGameStep(EGameStep NewStep)
{
	GameStep = NewStep;

	if (HasAuthority())
	{
		OnReq_GameStepChange();
	}

	UE_LOG(LogTemp, Error, TEXT("GameStep Change!"));
}

EGameStep AAAFGameState::GetGameStep()
{
	return GameStep;
}

void AAAFGameState::BeginPlay()
{
	Super::BeginPlay();
}

void AAAFGameState::SetLandCount(uint8 firstLand, uint8 SecondsLand)
{
	AbundanceLand = firstLand;
	FamineLand = SecondsLand;
}

void AAAFGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAAFGameState, GameStep);
	DOREPLIFETIME(AAAFGameState, AbundanceLand);
	DOREPLIFETIME(AAAFGameState, FamineLand);
}

void AAAFGameState::OnReq_GameStepChange()
{

	if (EventDisptacherGameStepChange.IsBound())
	{
		EventDisptacherGameStepChange.Broadcast(GameStep);
		UE_LOG(LogTemp, Error, TEXT("GameStep BroadCast"));
	}
}
