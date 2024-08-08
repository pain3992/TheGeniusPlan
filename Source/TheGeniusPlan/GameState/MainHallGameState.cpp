// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/GameState/MainHallGameState.h"
#include "GameFramework/PlayerState.h"
#include "TheGeniusPlan/PlayerState/MainHallPlayerState.h"
#include "Net/UnrealNetwork.h"

void AMainHallGameState::OnRep_PlayerRankings()
{
    PlayerRankings.Empty();

    for (APlayerState* PS : PlayerArray)
    {
        AMainHallPlayerState* PlayerState = Cast<AMainHallPlayerState>(PS);
        if (PlayerState)
        {
            FPlayerRankingData RankingData;
            RankingData.PlayerName = PlayerState->PlayerName;
            RankingData.Score = PlayerState->GetPlayerScore(); // Use GetPlayerScore() instead of direct access

            PlayerRankings.Add(RankingData);
        }
    }

    // Trigger any necessary updates or UI refreshes here if needed
    UpdatePlayerRankings(); // Example function to update the UI
}

void AMainHallGameState::UpdatePlayerRankings()
{
    // Notify HUD or other components about the updated rankings
}

void AMainHallGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMainHallGameState, PlayerRankings);
}
