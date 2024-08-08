// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/PlayerState/MainHallPlayerState.h"
#include "TheGeniusPlan/Widget/MainHallUserWidget.h"
#include "TheGeniusPlan/HUD/MainHallHUD.h"
#include "Net/UnrealNetwork.h"

int32 AMainHallPlayerState::GetPlayerScore() const
{
    return GetScore();
}

void AMainHallPlayerState::SetPlayerScore(int32 NewScore)
{
    SetScore(NewScore);
}

void AMainHallPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMainHallPlayerState, PlayerName);
}
