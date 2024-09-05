// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MainGameStateBase.generated.h"

/**
 *
 */
UCLASS()
class THEGENIUSPLAN_API AMainGameStateBase : public AGameState
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    // 플레이어 목록
    UPROPERTY(ReplicatedUsing = OnRep_PlayingPlayers, VisibleAnywhere, BlueprintReadOnly, Category = "GameState")
    TArray<AGeniusPlayerState *> PlayingPlayers;

    // 플레이어를 목록에서 추가 함수
    void AddPlayer(AGeniusPlayerState *NewPlayerState);
    // 플레이어를 목록에서 제거하는 함수
    void RemovePlayer(AGeniusPlayerState *RemovePlayerState);

    AMainGameStateBase();

    // 플레이어 상태 정보를 반환하는 함수
    UFUNCTION(BlueprintCallable, Category = "PlayerData")
    TArray<AGeniusPlayerState *> GetAllPlayingPlayers() const;

    // 카운트다운 시작 함수
    virtual void StartCountdown(int32 InitialCountdownTime);

    UFUNCTION()
    virtual void OnRep_PlayingPlayers() const;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;

    virtual void CountdownFinished();

    // 전체 라운드
    UPROPERTY(ReplicatedUsing = OnRep_TotalRound)
    int32 TotalRound;

    // 현재 라운드
    UPROPERTY(ReplicatedUsing = OnRep_CurrentRound)
    int32 CurrentRound;

    // 전체 라운드를 설정하는 함수
    UFUNCTION(BlueprintCallable, Category = "Game Rules")
    void SetTotalRound(int32 NewTotalRound);

    // 현재 라운드를 설정하는 함수
    UFUNCTION(BlueprintCallable, Category = "Game Rules")
    void SetCurrentRound(int32 NewCurrentRound);

    // PossibleGameModes 개수
    UPROPERTY(ReplicatedUsing = OnRep_PossibleGameModesCount)
    int32 PossibleGameModesCount;

    // PossibleGameModes 개수 설정 함수
    void SetPossibleGameModesCount(int32 Count);

protected:
    // 카운트다운 변수가 변경될 때 클라이언트에서 호출되는 함수
    UFUNCTION()
    void OnRep_CountdownTime() const;

    UFUNCTION()
    void OnRep_TotalRound() const;

    UFUNCTION()
    void OnRep_CurrentRound() const;

    UFUNCTION()
    void OnRep_PossibleGameModesCount() const;

    UPROPERTY(ReplicatedUsing = OnRep_CountdownTime)
    int32 CountdownTime;

private:
    FTimerHandle CountdownTimerHandle;

    virtual void UpdateCountdown();

};