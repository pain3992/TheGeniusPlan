// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "PlayerRankingUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UPlayerRankingUserWidget : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Player Ranking")
    void UpdateData(const FPlayerRankingData& PlayerRankingData);

protected:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Text_PlayerName;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Text_Score;
};