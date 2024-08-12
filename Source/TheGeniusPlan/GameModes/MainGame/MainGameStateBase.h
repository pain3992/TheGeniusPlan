// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GameState")
	TArray<AGeniusPlayerState*> PlayingPlayers;

	// 플레이어를 목록에서 추가 함수
	void AddPlayer(AGeniusPlayerState *NewPlayerState);
	// 플레이어를 목록에서 제거하는 함수
	void RemovePlayer(AGeniusPlayerState *RemovePlayerState);
	
    AMainGameStateBase();

    // 플레이어 상태 정보를 반환하는 함수
    UFUNCTION(BlueprintCallable, Category = "PlayerData")
    TArray<AGeniusPlayerState*> GetAllPlayingPlayers() const;

    // 플레이어 순위를 업데이트하는 함수
    UFUNCTION(BlueprintCallable, Category = "PlayerData")
    void UpdatePlayerRankings();

    // 플레이어 랭킹 데이터
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Ranking")
    TArray<UPlayerRankingData*> PlayerRankings;
};