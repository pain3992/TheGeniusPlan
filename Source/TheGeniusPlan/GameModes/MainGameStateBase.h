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
    UFUNCTION(BlueprintCallable, Category = "Countdown")
    void StartCountdown(int32 InitialCountdownTime);

    UFUNCTION()
    void OnRep_PlayingPlayers() const;

    UFUNCTION(NetMulticast, Reliable)
    void ShowWidgetPlayerRanking();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;

protected:
    // 카운트다운 변수가 변경될 때 클라이언트에서 호출되는 함수
    UFUNCTION()
    void OnRep_CountdownTime() const;

    UPROPERTY(ReplicatedUsing = OnRep_CountdownTime)
    int32 CountdownTime;

private:
    FTimerHandle CountdownTimerHandle;

    void UpdateCountdown();
    void CountdownFinished();
};