// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/GameModes/GeniusGameInstance.h"

void UGeniusGameInstance::SavePlayerScore(APlayerState *PlayerState, int32 Score)
{
    if (PlayerState)
    {
        Players.Add(PlayerState);
        PlayerScores.Add(PlayerState, Score);
    }
}

void UGeniusGameInstance::SavePlayer(APlayerState *PlayerState)
{
    if (PlayerState)
    {
        Players.Add(PlayerState);
    }
}

APlayerState *UGeniusGameInstance::FindPlayer(const APlayerState *GeniusPlayerState)
{
    if (!GeniusPlayerState)
    {
        return nullptr;
    }

    for (APlayerState *Player : Players)
    {
        if (Player == GeniusPlayerState)
        {
            return Player;
        }
    }
    return nullptr;
}

int32 UGeniusGameInstance::GetPlayerScore(APlayerState *PlayerState) const
{
    // PlayerState->Score;
    const int32 *FoundScore = PlayerScores.Find(PlayerState);
    return FoundScore ? *FoundScore : 0;
}

void UGeniusGameInstance::AddPlayerScore(APlayerState *PlayerState, int32 ScoreToAdd)
{
    if (PlayerState)
    {
        int32 &Score = PlayerScores.FindOrAdd(PlayerState);
        Score += ScoreToAdd;
    }
}
