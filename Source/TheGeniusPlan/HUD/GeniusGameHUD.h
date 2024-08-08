// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GeniusGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AGeniusGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGeniusGameHUD();

	virtual void BeginPlay() override;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Widget")
	// TSubclassOf<class >
};
