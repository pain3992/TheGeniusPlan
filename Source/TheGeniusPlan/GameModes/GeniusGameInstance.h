// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../Player/AAFPlayerState.h"
#include "GeniusGameInstance.generated.h"

UCLASS()
class THEGENIUSPLAN_API UGeniusGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    // 각 플레이어의 점수를 저장하는 맵
    UPROPERTY(BlueprintReadWrite, Category = "Scores")
    TMap<APlayerState*, int32> PlayerScores;
    TArray<APlayerState*> Players;

    // 점수 저장 함수
    void SavePlayerScore(APlayerState* PlayerState, int32 Score);

    // 점수 가져오기 함수
    int32 GetPlayerScore(APlayerState* PlayerState) const;

    // 기존 점수에 더하는 함수
    void AddPlayerScore(APlayerState* PlayerState, int32 ScoreToAdd);
	
public:
	UPROPERTY()
	ESelectedLand GI_SelectedLand;
	
};
