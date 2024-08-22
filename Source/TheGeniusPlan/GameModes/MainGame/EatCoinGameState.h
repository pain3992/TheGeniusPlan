// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameStateBase.h"
#include "TheGeniusPlan/Player/EatCoinPlayerState.h"
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
	//virtual void OnRep_PlayingPlayers() const override;
	//virtual void ShowWidgetPlayerRanking_Implementation() override;

	// 코인 점수 목록
	UPROPERTY(ReplicatedUsing = OnRep_PlayerCoinScores, VisibleAnywhere, BlueprintReadOnly, Category = "GameState")
	TArray<AEatCoinPlayerState*> PlayerCoinScores;

	// 코인 점수를 반환하는 함수
	UFUNCTION(BlueprintCallable, Category = "Coin Data")
	TArray<AEatCoinPlayerState*> GetAllPlayerCoinScores() const;

	void UpdatePlayerCoinScores();

	UFUNCTION()
	virtual void OnRep_PlayerCoinScores() const;

	UFUNCTION(NetMulticast, Reliable)
	virtual void ShowWidgetCoinRanking();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};