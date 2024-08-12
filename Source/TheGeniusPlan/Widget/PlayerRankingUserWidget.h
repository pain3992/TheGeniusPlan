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
class THEGENIUSPLAN_API UPlayerRankingUserWidget : public UUserWidget , public IUserObjectListEntry
{
    GENERATED_BODY()

public:
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* Text_PlayerName;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* Text_Score;

    UFUNCTION(BlueprintCallable, Category = "Player Ranking")
    void SetPlayerName(const FString& PlayerName);

    UFUNCTION(BlueprintCallable, Category = "Player Ranking")
    void SetScore(int32 Score);

private:
    UPROPERTY()
    FString PlayerName;

    UPROPERTY()
    int32 Score;
};