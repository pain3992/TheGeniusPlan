// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerRankingData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayerRankingData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Ranking")
    FString PlayerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Ranking")
    int32 Score;

    FPlayerRankingData()
        : PlayerName(TEXT("Default Player")), Score(0) {}
};
