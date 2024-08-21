// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameStateBase.h"
#include "EatCoinGameState.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AEatCoinGameState : public AMainGameStateBase
{
	GENERATED_BODY()

public:
	
	AEatCoinGameState();

	//  virtual void OnRep_Score() override;
	virtual void OnRep_PlayingPlayers() const override;
	virtual void ShowWidgetPlayerRanking_Implementation() override;
};