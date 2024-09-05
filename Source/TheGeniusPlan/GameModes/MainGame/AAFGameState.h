// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGameStateBase.h"
#include "AAFGameState.generated.h"

UENUM()
enum class EGameStep : uint8
{
	None UMETA(Displayname = "None"),
	SetLocation UMETA(DisplayName = "ResetLocation"),
	RoundStart UMETA(Displayname = "RoundStart"),
	RoundEnd UMETA(DisplayName = "RoundEnd"),
	GameEnd UMETA(DisplayName = "GameEnd")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventDispatcher_GameStepChange, EGameStep, NewStep);

UCLASS()
class THEGENIUSPLAN_API AAAFGameState : public AMainGameStateBase
{
	GENERATED_BODY()

public:
	AAAFGameState();

	UPROPERTY()
	FEventDispatcher_GameStepChange EventDisptacherGameStepChange;

	UFUNCTION()
	void SetGameStep(EGameStep NewGameStep);

	UFUNCTION()
	EGameStep GetGameStep();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void RequestGameStepReset();

	UFUNCTION(Server, Reliable)
	void ResponseGameStepReset();

	UFUNCTION()
	void RequestSetPlayerLocation();

	UFUNCTION(Server, Reliable)
	void ResponseSetPlayerLocation();

	UFUNCTION(Server, Reliable)
	void ResponseSendLocationByClient();

	UFUNCTION(Server, Reliable)
	void ChangeGameStepByRound();

	UFUNCTION()
	void RequestGameStepEnd();

	UFUNCTION(Server, Reliable)
	void ResponseGameStepEnd();

	UFUNCTION()
	void RequestWinnerCheck();

	UFUNCTION(Server, Reliable)
	void ResponsetWinnerCheck();

protected:
	UPROPERTY()
	uint8 StageCount;

	UPROPERTY(ReplicatedUsing = OnReq_GameStepChange)
	EGameStep GameStep;

	UFUNCTION()
	void OnReq_GameStepChange();

	FTimerHandle GameModeFirstHandle;
	FTimerHandle GameModeSecondHandle;
	FTimerHandle GameModeThirdHandle;
	FTimerHandle GameModeFHandle;
	FTimerHandle GameModeFiveHandle;

	UPROPERTY(Replicated)
	TArray<FVector> PlayerLocations;

};
