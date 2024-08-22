// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/Player/GeniusPlayerState.h"
#include "EatCoinPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AEatCoinPlayerState : public AGeniusPlayerState
{
	GENERATED_BODY()

public:
	AEatCoinPlayerState();

	UPROPERTY(ReplicatedUsing = OnRep_CoinScore, BlueprintReadOnly, Category = "Coin")
	int CoinScore;

	UPROPERTY(ReplicatedUsing = OnRep_BoostTime, BlueprintReadOnly, Category = "Boost")
	float BoostTimeLeft;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Boost")
	bool bIsBoostActive;

	UFUNCTION()
	virtual void OnRep_BoostTime();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void StartBoostCountdown(float Duration);
	void UpdateBoostCountdown();

	float OriginalSpeed = 500.0f;

	void AddCoinScore(int32 Amount);

	UFUNCTION()
	void OnRep_CoinScore() const;

	int32 GetCoinScore() const;

private:
	FTimerHandle BoostCountdownTimerHandle;
	
};
