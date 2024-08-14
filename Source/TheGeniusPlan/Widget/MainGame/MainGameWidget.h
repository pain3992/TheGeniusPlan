// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheGeniusPlan/Widget/MainGame/PlayerRankingUserWidget.h"
#include "TheGeniusPlan/gameModes/MainGame/MainGameStateBase.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "Components/ListView.h"
#include "MainGameWidget.generated.h"


UCLASS()
class THEGENIUSPLAN_API UMainGameWidget : public UUserWidget
{
    GENERATED_BODY()


public:
    void SetHUD(class AMainGameHUD* InHUD);

    UFUNCTION(BlueprintCallable, Category = "Player Ranking")
    void UpdatePlayerList(const TArray<AGeniusPlayerState*>& PlayingPlayersArray);

    AMainGameHUD* MainGameHUD;

    UFUNCTION(BlueprintCallable, Category = "Countdown")
    void UpdateCountdownDisplay(int32 CountdownTimeInSeconds);  

protected:
    virtual void NativeConstruct() override;

    // ListView를 참조
    UPROPERTY(meta = (BindWidget))
    class UListView* ListView_PlayerRanking;


    UPROPERTY(meta = (BindWidget))
    class UButton* Button_Hint;

    UFUNCTION()
    void OnHelpButtonClicked();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Ranking")
    TSubclassOf<class UPlayerRankingUserWidget> PlayerRankingUserWidgetClass;




private:
    FTimerHandle CountdownTimerHandle;
    int32 CountdownTime;

    UPROPERTY(meta=(BindWidget))
    class UTextBlock* Text_Countdown;

   // void LoadData();
};