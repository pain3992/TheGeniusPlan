// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeniusPlayerController.h"
#include "AAFPlayerController.generated.h"


UCLASS()
class THEGENIUSPLAN_API AAAFPlayerController : public AGeniusPlayerController
{
	GENERATED_BODY()

public:
	AAAFPlayerController();

	virtual void BeginPlay() override;

	UFUNCTION()
	void BindDispatcher();

	UPROPERTY()
	FTimerHandle TimerHandletwo;

	UFUNCTION()
	void GameStepChange(EGameStep NewStep);

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY()
	TObjectPtr<class AAAFGameState> GameState;

	UFUNCTION()
	void MoveActor();

	UFUNCTION(Server, Reliable)
	void Server_MoveActor();

	UFUNCTION(NetMulticast, Reliable)
	void Client_MoveActor();

	UPROPERTY()
	TObjectPtr<class AAAFPlayerState> CastPlayerState;

	UFUNCTION()
	void RequestGameStateFunction();

	UFUNCTION(Server, Reliable)
	void ResponseGameStateFunction();




};
