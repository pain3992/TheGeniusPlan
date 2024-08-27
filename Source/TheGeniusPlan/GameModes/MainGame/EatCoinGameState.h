// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGameStateBase.h"
#include "TheGeniusPlan/Player/EatCoinPlayerState.h"
#include "EatCoinGameState.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AEatCoinGameState : public AMainGameStateBase
{
	GENERATED_BODY()

public:
	AEatCoinGameState();


	// 코인 점수 목록
	UPROPERTY(ReplicatedUsing = OnRep_PlayerCoinScores, VisibleAnywhere, BlueprintReadOnly, Category = "GameState")
	TArray<AEatCoinPlayerState*> PlayerCoinScores;

	// 코인 점수를 반환하는 함수
	UFUNCTION(BlueprintCallable, Category = "Coin Data")
	TArray<AEatCoinPlayerState*> GetAllPlayerCoinScores() const;

	// 코인 점수 업데이트
	void UpdatePlayerCoinScores();

	UFUNCTION()
	virtual void OnRep_PlayerCoinScores() const;

	// (라운드)카운트다운 종료
	virtual void CountdownFinished() override; 

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnCountdownFinished();

	// EatCoin 게임시작까지 남은 카운트다운 시작 함수
	UFUNCTION(BlueprintCallable, Category = "Countdown")
	void StartECGameCount(int32 InitialCountdownTime);

	// EatCoin 게임시작까지 남은 시간 카운트다운 업데이트 함수
	void UpdateECGameCount();

	UFUNCTION()
	void OnRep_ECGameCountdownTime() const;

	UPROPERTY(ReplicatedUsing = OnRep_ECGameCountdownTime)
	int32 ECGameCountdownTime;

	// EatCoin 게임시작까지 남은 카운트다운 종료됐을 때 실행되는 함수
	void ECGameCountdownFinished();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnECGameCountdownFinished();

	// 1-3위에게 랭크 점수 부여
	void AwardTopPlayers();

	UFUNCTION()
	void OnRep_MovePlayersToStart() const;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	// EC 카운트다운 타이머 핸들러
	FTimerHandle ECGameCountdownTimerHandle;

	// 10초 후에 레벨 이동을 처리하는 함수 선언
	void TravelToNextLevel();

	// 마지막 라운드인지 여부를 체크
	
	// 레벨 이동 타이머 핸들러
	FTimerHandle ServerTravelTimerHandle;
};