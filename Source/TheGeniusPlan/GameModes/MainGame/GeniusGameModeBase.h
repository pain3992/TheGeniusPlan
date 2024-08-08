// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GeniusGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AGeniusGameModeBase : public AGameMode
{
	GENERATED_BODY()
public:
	AGeniusGameModeBase();

protected:
	virtual void BeginPlay() override;

	void HandleGameStart();
	// void HandleRoundEnd();
	// void CheckForOverallWinner();
	// void TransitionToNextRound();
	// void EndMatch(int32 WinningPlayerId);
	void SelectNextGameMode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Rounds", meta=(AllowPrivateAccess = "true"))
	int32 TotalRounds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Rounds", meta=(AllowPrivateAccess = "true"))
	int32 CurrentRound;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wins", meta=(AllowPrivateAccess = "true"))
	TMap<int32, int32> PlayerWins;

	UPROPERTY(EditDefaultsOnly, Category="GameModes")
	TArray<TSubclassOf<AGameMode>> PossibleGameModes;
};
