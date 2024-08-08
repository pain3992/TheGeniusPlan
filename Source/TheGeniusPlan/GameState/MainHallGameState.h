// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "MainHallGameState.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AMainHallGameState : public AGameState
{
    GENERATED_BODY()

public:
    UPROPERTY(ReplicatedUsing = OnRep_PlayerRankings)
    TArray<FPlayerRankingData> PlayerRankings;

    UFUNCTION()
    void OnRep_PlayerRankings();

    void UpdatePlayerRankings();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};