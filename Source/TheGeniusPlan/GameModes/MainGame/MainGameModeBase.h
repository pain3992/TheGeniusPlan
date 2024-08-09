// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainGameModeBase.generated.h"

/**
 * @description 메인 게임모드 부모 클래스로 사용 예정
 * @see 게임의 규칙과 관련된 로직이 주로 사용될 예정
 */
UCLASS()
class THEGENIUSPLAN_API AMainGameModeBase : public AGameMode
{
	GENERATED_BODY()
public:
	AMainGameModeBase();

	UFUNCTION(BlueprintCallable, Category="GameMode")
	void SelectNextGameMode();
	
protected:
	virtual void BeginPlay() override;

	void HandleGameStart();
	// void HandleRoundEnd();
	// void CheckForOverallWinner();
	// void TransitionToNextRound();
	// void EndMatch(int32 WinningPlayerId);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Rounds", meta=(AllowPrivateAccess = "true"))
	int32 TotalRounds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Rounds", meta=(AllowPrivateAccess = "true"))
	int32 CurrentRound;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wins", meta=(AllowPrivateAccess = "true"))
	TMap<int32, int32> PlayerWins;

	UPROPERTY(EditDefaultsOnly, Category="GameModes")
	TArray<TSubclassOf<AGameMode>> PossibleGameModes;
};
