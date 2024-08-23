// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "Components/ListView.h"
#include "TheGeniusPlan/Widget/MainGame/CoinScoreItemWidget.h"
#include "EatCoinEndWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UEatCoinEndWidget : public UUserWidget
{
	GENERATED_BODY()

public:

protected:
	UPROPERTY(meta = (BindWidget))
	class UListView* ListView_Ranking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eat Coin Ranking")
	TSubclassOf<class UCoinScoreItemWidget> CoinScoreItemWidgetClass;
};
