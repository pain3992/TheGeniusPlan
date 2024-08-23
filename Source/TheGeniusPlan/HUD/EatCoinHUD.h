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

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    UEatCoinEndWidget* GetEatCoinEndWidget() const { return EatCoinEndWidget; }

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    UEatCoinMenualWidget* GetEatCoinMenualWidget() const { return EatCoinMenualWidget; }

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    UEatCoinStartWidget* GetEatCoinStartWidget() const { return EatCoinStartWidget; }

    // 게임 종료 위젯 띄우기
    void ShowEatCoinEndWidget();

    // 매뉴얼+게임시작까지 남은시간 카운트다운 위젯 지우기
    void CollapsedECMenualWidget();

    // 게임 시작 위젯 띄우기 + 없애기
    void ShowGameStartWidget();
    void HideGameStartWidget();

private:
    // EatCoin 게임의 기본 위젯
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UEatCoinWidget> EatCoinWidgetClass;

    UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UEatCoinWidget> EatCoinWidget;

    // 게임이 종료되었음을 알리는 위젯
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UEatCoinEndWidget> EatCoinEndWidgetClass;

    UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
    TObjectPtr <UEatCoinEndWidget> EatCoinEndWidget;

    // 게임이 시작하기 전 설명 + 게임시작까지 남은 시간 카운트다운하는 위젯
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UEatCoinMenualWidget> EatCoinMenualWidgetClass;

    UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UEatCoinMenualWidget> EatCoinMenualWidget;

    // 게임 시작을 알리는 위젯
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UEatCoinStartWidget> EatCoinStartWidgetClass;

    UPROPERTY(BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UEatCoinStartWidget> EatCoinStartWidget;

    FTimerHandle TimerHandle_HideWidget;
};

