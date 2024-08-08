// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerTeamUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UPlayerTeamUserWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
    // Called when the game starts or when spawned
    virtual void NativeConstruct() override;

public:
    // Sets the player and team data
    void SetPlayerData(const FString& PlayerName, const FString& TeamName);

private:
    // UI elements for player and team information
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Text_PlayerName;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Text_TeamName;
};