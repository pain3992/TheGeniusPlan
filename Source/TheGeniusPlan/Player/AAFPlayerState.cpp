// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFPlayerState.h"
#include "TheGeniusPlan/GameModes/MainGame/AAFGameState.h"
#include "Net/UnrealNetwork.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "TheGeniusPlan/Player/GeniusPlayerController.h"

void AAAFPlayerState::BeginPlay()
{
	Super::BeginPlay();
	Lose = false;
}

AAAFPlayerState::AAAFPlayerState()
	: Location{ 0, 0, 0 }
{
	
}

void AAAFPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAAFPlayerState, Lose);
	DOREPLIFETIME(AAAFPlayerState, Location);
	DOREPLIFETIME(AAAFPlayerState, win);
}
