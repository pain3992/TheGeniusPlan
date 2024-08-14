// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerRankingData.generated.h"

UCLASS(BlueprintType)
class THEGENIUSPLAN_API UPlayerRankingData : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Ranking")
    FString PlayerName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Ranking")
    int32 Score;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Piece")
    int32 PieceCount;

};
