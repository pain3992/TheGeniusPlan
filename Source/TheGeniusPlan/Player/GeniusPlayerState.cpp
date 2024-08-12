// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Player/GeniusPlayerState.h"
#include "TheGeniusPlan/Widget/MainGame/MainGameWidget.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "Net/UnrealNetwork.h"

int32 AGeniusPlayerState::GetPlayerScore() const
{
    return GetScore();
}

void AGeniusPlayerState::SetPlayerScore(int32 NewScore)
{
    SetScore(NewScore);
}

void AGeniusPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGeniusPlayerState, PlayerName);
}
