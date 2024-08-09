// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameModeBase.h"
#include "GyulhapGameMode.generated.h"

/**
 * @description 결합게임 모드 WIP
 */
UCLASS()
class THEGENIUSPLAN_API AGyulhapGameMode : public AMainGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
