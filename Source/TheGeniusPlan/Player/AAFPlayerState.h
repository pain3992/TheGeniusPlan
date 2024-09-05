// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeniusPlayerState.h"
#include "AAFPlayerState.generated.h"

UCLASS()
class THEGENIUSPLAN_API AAAFPlayerState : public AGeniusPlayerState
{
	GENERATED_BODY()

protected:

public:

	AAAFPlayerState();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	bool Lose;

	UPROPERTY(Replicated)
	uint8 win;

	UPROPERTY(Replicated)
	FVector Location;
};
