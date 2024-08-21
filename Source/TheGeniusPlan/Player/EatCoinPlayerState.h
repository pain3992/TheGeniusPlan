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

	// Remaining time for the boost in seconds
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Boost")
    float RemainingBoostTime;

    // Function to update the remaining boost time
    UFUNCTION()
    void UpdateBoostTime(float DeltaTime);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    virtual void Tick(float DeltaTime) override;
};
