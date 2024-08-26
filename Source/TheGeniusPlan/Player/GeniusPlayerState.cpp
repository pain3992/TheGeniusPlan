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

void AGeniusPlayerState::AddScore(int32 Amount)
{
    // 점수 증가
    SetScore(GetScore() + Amount);

    // 로그 출력
    UE_LOG(LogTemp, Log, TEXT("Player %s's score increased by %d. New Score!: %d"),
        *PlayerName, Amount, static_cast<int>(GetScore()));
}

void AGeniusPlayerState::OnRep_Score()
{
    if (GetWorld()->GetGameState<AMainGameStateBase>())
    {
        AMainGameStateBase* MainGameState = GetWorld()->GetGameState<AMainGameStateBase>();
        MainGameState->OnRep_PlayingPlayers();
    }
}

void AGeniusPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGeniusPlayerState, PlayerName);
   // DOREPLIFETIME(AGeniusPlayerState, Score);
}
