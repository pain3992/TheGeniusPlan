// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGameModeBase.h"
#include "OpenPassGameMode.generated.h"

/**
 * @description 오픈패스 게임모드 (임시 게임)
 */
UCLASS()
class THEGENIUSPLAN_API AOpenPassGameMode : public AMainGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
};
