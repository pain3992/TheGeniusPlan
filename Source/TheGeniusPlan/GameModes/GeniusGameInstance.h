// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../Player/AAFPlayerState.h"
#include "GeniusGameInstance.generated.h"

UCLASS()
class THEGENIUSPLAN_API UGeniusGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	ESelectedLand GI_SelectedLand;
	
};
