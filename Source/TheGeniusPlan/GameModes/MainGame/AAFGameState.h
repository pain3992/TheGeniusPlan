// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainHallGameState.h"
#include "AAFGameState.generated.h"

UCLASS()
class THEGENIUSPLAN_API AAAFGameState : public AMainHallGameState
{
	GENERATED_BODY()

public:
	AAAFGameState();

	UFUNCTION()
	bool CheckPlayerState();

	UFUNCTION()
	void ShowPlayerState();


protected:
	UPROPERTY()
	uint8 AbundanceLand;

	UPROPERTY()
	uint8 FamineLand;
	
};
