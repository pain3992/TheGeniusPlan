// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameModeBase.h"
#include "EndGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AEndGameModeBase : public AMainGameModeBase
{
	GENERATED_BODY()

public:
	AEndGameModeBase();

	virtual void BeginPlay() override;

	UFUNCTION()
	void PlayerSendNumber();

	FTimerHandle Timer;


	
};
