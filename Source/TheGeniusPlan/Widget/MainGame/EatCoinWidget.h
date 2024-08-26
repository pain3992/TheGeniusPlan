// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheGeniusPlan/gameModes/MainGameStateBase.h"
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
	void UpdateEatCoinPlayerList(const TArray<AEatCoinPlayerState*>& PlayerCoinScoresArray);

	void UpdateBoostTimer();

	FTimerHandle UpdateTimerHandle;

	// 리스트뷰를 화면 중앙으로 이동시키는 함수
	UFUNCTION(BlueprintCallable, Category = "UI")
	void MoveListViewToCenter();

protected:
	virtual void NativeConstruct() override;

	// ListView를 참조
	UPROPERTY(meta = (BindWidget))
	class UListView* ListView_CoinScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eat Coin Ranking")
	TSubclassOf<class UCoinScoreItemWidget> CoinScoreItemWidgetClass;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_BoostTimer;

private:
	float RemainingBoostTime = 0.0f; // Track remaining boost time
	
};
