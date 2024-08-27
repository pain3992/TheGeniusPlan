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

	// 리스트뷰를 화면 중앙으로 이동시키는 함수 (라운드 종료 때마다 보여줌)
	UFUNCTION(BlueprintCallable, Category = "UI")
	void MoveListViewToCenter();

	// 리스트뷰의 위치를 원위치로 복구시키는 함수 (라운드가 새로 시작할 때마다 실행)
	UFUNCTION(BlueprintCallable, Category = "UI")
	void MoveListViewToOriginalPosition();

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
