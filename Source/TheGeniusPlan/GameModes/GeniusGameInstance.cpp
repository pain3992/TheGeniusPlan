// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/GameModes/GeniusGameInstance.h"

void UGeniusGameInstance::SavePlayerScore(APlayerState* PlayerState, int32 Score)
{
    
    if (PlayerState)
    {
        Players.Add(PlayerState);
        PlayerScores.Add(PlayerState, Score);
    }
}

int32 UGeniusGameInstance::GetPlayerScore(APlayerState* PlayerState) const
{
    // PlayerState->Score;
    const int32* FoundScore = PlayerScores.Find(PlayerState);
    return FoundScore ? *FoundScore : 0;
}

void UGeniusGameInstance::AddPlayerScore(APlayerState* PlayerState, int32 ScoreToAdd)
{
    if (PlayerState)
    {
        int32& Score = PlayerScores.FindOrAdd(PlayerState);
        Score += ScoreToAdd;
    }
}
