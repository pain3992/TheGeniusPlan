// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "CoinScoreItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UCoinScoreItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* Text_EatCoinPlayerName;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* Text_EatCoinScore;

    UFUNCTION(BlueprintCallable, Category = "Eat Coin Ranking")
    void SetEatCoinPlayerName(const FString& PlayerName);

    UFUNCTION(BlueprintCallable, Category = "Eat Coin Ranking")
    void SetEatCoinScore(int32 Score);

private:
    UPROPERTY()
    FString PlayerName;

    UPROPERTY()
    int32 Score;
	
};
