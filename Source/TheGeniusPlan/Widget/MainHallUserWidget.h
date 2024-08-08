// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheGeniusPlan/Widget/PlayerRankingUserWidget.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "MainHallUserWidget.generated.h"

UCLASS()
class THEGENIUSPLAN_API UMainHallUserWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UButton* Button_Help;

    UFUNCTION()
    void OnHelpButtonClicked();


    UPROPERTY(meta = (BindWidget))
    UListView* ListView_PlayerRanking;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Ranking")
    TSubclassOf<UPlayerRankingUserWidget> PlayerRankingUserWidgetClass;

public:
    void SetHUD(class AMainHallHUD* InHUD);

    // 한글 주석 테스트
    UFUNCTION(BlueprintCallable, Category = "Player Ranking")
    void UpdateRankingList(const TArray<FPlayerRankingData>& Rankings);

private:
    AMainHallHUD* HUD;
};