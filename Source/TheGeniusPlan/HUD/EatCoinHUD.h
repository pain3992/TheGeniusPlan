// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "EatCoinHUD.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AEatCoinHUD : public AMainGameHUD
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay() override;

    AEatCoinHUD();

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    UEatCoinWidget* GetEatCoinWidget() const { return EatCoinWidget; }

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UEatCoinWidget> EatCoinWidgetClass;

    UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UEatCoinWidget> EatCoinWidget;
};

