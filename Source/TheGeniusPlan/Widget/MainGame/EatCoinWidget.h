// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheGeniusPlan/gameModes/MainGame/MainGameStateBase.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "Components/ListView.h"
#include "TheGeniusPlan/Widget/MainGame/CoinScoreItemWidget.h"
#include "EatCoinWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UEatCoinWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Eat Coin Ranking")
	void UpdateEatCoinPlayerList(const TArray<AGeniusPlayerState*>& PlayingPlayersArray);

protected:
	virtual void NativeConstruct() override;

	// ListView를 참조
	UPROPERTY(meta = (BindWidget))
	class UListView* ListView_CoinScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eat Coin Ranking")
	TSubclassOf<class UCoinScoreItemWidget> CoinScoreItemWidgetClass;
	
};