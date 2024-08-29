// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "EndPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AEndPlayerState : public APlayerState
{
	GENERATED_BODY()
	

public:
	virtual void BeginPlay() override;

	UPROPERTY(Replicated)
	uint8 PlayerNumber;

	UFUNCTION()
	void PrintInstanceNumber();

	UFUNCTION()
	void PlayerStateNumberSet(uint8 NewNumber);

	FTimerHandle TimerHandle;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
};
