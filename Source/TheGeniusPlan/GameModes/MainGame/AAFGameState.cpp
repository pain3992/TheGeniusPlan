// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFGameState.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "Net/UnrealNetwork.h"
#include "TheGeniusPlan/Player/GeniusPlayerController.h"

AAAFGameState::AAAFGameState()
{
	StageCount = 0;
}

void AAAFGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
