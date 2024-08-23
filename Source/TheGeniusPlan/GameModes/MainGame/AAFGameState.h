// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGameStateBase.h"
#include "AAFGameState.generated.h"

UENUM()
enum class EGameStep : uint8
{
	None UMETA(Displayname = "None"),
	Vote UMETA(Displayname = "Vote"),
	Result UMETA(Displayname = "Result"),
	MoveActor UMETA(DisplayName = "MoveActor"),
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

	//UFUNCTION()
	//void CheckPlayerAllSelected();

	virtual void BeginPlay() override;

	UFUNCTION()
	void SetLandCount(uint8 firstLand, uint8 SecondsLand);

	UPROPERTY(Replicated)
	uint8 AbundanceLand;

	UPROPERTY(Replicated)
	uint8 FamineLand;

	//UPROPERTY(Replicated)
	//double Timer;

protected:
	UPROPERTY()
	uint8 StageCount;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnReq_GameStepChange)
	EGameStep GameStep;

	UFUNCTION()
	void OnReq_GameStepChange();


};
