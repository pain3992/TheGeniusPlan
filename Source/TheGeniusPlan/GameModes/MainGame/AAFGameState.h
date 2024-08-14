// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameStateBase.h"
#include "AAFGameState.generated.h"

UCLASS()
class THEGENIUSPLAN_API AAAFGameState : public AMainGameStateBase
{
	GENERATED_BODY()

public:
	AAAFGameState();


protected:

	UPROPERTY()
	uint8 StageCount;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


};
