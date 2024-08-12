// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainHallPlayerState.h"
#include "AAFPlayerState.generated.h"

UENUM()
enum class ESelectedLand : uint8
{
	None UMETA(Displayname = "None"),
	AbundanceLand UMETA(Displayname = "Abundance"),
	FamineLand UMETA(Displayname = "FamineLand"),

};

UCLASS()
class THEGENIUSPLAN_API AAAFPlayerState : public AMainHallPlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(ReplicatedUsing = CheckAllPlayerLand)
	ESelectedLand SelectedLand;

	UFUNCTION()
	void CheckAllPlayerLand();

public:
	AAAFPlayerState();

	UFUNCTION()
	void ChangeLand(ESelectedLand Select);

	UFUNCTION()
	ESelectedLand GetSelectedLand();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
