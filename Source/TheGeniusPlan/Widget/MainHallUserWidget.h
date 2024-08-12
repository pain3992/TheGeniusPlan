// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheGeniusPlan/Widget/PlayerRankingUserWidget.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "Components/ListView.h"
#include "MainHallUserWidget.generated.h"


UCLASS()
class THEGENIUSPLAN_API UMainHallUserWidget : public UUserWidget
{
    GENERATED_BODY()


public:
    void SetHUD(class AMainHallHUD* InHUD);

    UFUNCTION(BlueprintCallable, Category = "Player Ranking")
    void UpdatePlayerList(const TArray<UPlayerRankingData*>& PlayerRankingDataArray);

    AMainHallHUD* MainHallHUD;


protected:
    virtual void NativeConstruct() override;

    // ListView를 참조
    UPROPERTY(meta = (BindWidget))
    class UListView* ListView_PlayerRanking;


    UPROPERTY(meta = (BindWidget))
    class UButton* Button_Help;

    UFUNCTION()
    void OnHelpButtonClicked();


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Ranking")
    TSubclassOf<class UPlayerRankingUserWidget> PlayerRankingUserWidgetClass;

private:
    

    void LoadData();
};