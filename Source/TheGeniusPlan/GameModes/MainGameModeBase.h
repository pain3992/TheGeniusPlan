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

	// 게임모드 선택하는 테스트 함수
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void SelectNextGameMode();

	// 게임 시작 함수
	virtual void HandleGameStart();

	// 라운드 종료 함수
	virtual void HandleRoundEnd();

	// 전체 승리자를 확인하는 함수
	void CheckRoundWinner();

	// 다음 라운드로 전환하는 함수
	virtual void TransitionToNextRound();

	// 게임 종료 및 승자 결정하는 함수
	void EndGame(int32 WinningPlayerId);

	// 게임 규칙을 적용하는 함수
	void SetGameRules();

	// 카운트 다운 함수
	virtual void SetCountdownRule();

	virtual void PostLogin(APlayerController *NewPlayer) override;
	virtual void Logout(AController *Exiting) override;

	// 카운트다운
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Rules", meta = (AllowPrivateAccess = "true"))
	int32 CountdownTimeInSeconds;

	FTimerHandle GameModeHandle;

	// 전체 라운드
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameRules", meta = (AllowPrivateAccess = "true"))
	int32 TotalRound;

	// 현재 라운드
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameRules", meta = (AllowPrivateAccess = "true"))
	int32 CurrentRound;

	// 전체 라운드 반환 함수
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	int32 GetTotalRound() const;

	// 현재 라운드 반환 함수
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	int32 GetCurrentRound() const;

protected:
	virtual void BeginPlay() override;

private:
	// 플레이어 ID, 스코어를 기록
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameRules", meta = (AllowPrivateAccess = "true"))
	TMap<int32, int32> PlayerScores;

	// 세션에 플레이중인 플레이어
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameRules", meta = (AllowPrivateAccess = "true"))
	TArray<APlayerController *> PlayingPlayers;

	// 게임에서 승리하기 위한 점수
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Rules", meta = (AllowPrivateAccess = "true"))
	int32 WinningScore;

	// 테스트용 변수, 변경 가능한 게임모드
	UPROPERTY(EditDefaultsOnly, Category = "GameModes")
	TArray<TSubclassOf<AGameMode>> PossibleGameModes;
};
