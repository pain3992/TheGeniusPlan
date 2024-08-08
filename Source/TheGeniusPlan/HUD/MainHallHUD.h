// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHallHUD.generated.h"


UENUM()
enum class MainHallWidgetType : uint8
{
    NONE UMETA(DisplayName = "NONE"),
    MainHallWidget UMETA(DisplayName = "MainHallWidget"),
    HelpWidget UMETA(DisplayName = "HelpWidget"),
    MAX UMETA(DisplayName = "MAX")
};

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AMainHallHUD : public AHUD
{
	GENERATED_BODY()

public:
    AMainHallHUD();

	virtual void BeginPlay() override;

    UFUNCTION()
    void ShowWidget(MainHallWidgetType type);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
    TSubclassOf<class UMainHallUserWidget> MainHallWidgetClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
    TSubclassOf<class UHelpUserWidget> HelpWidgetClass;

    // Function to set visibility of HelpWidget
    void SetHelpWidgetVisibility(ESlateVisibility Visibility);
    void ShowMouseCursor(bool bShowCursor);
    void UpdateRankingList();

protected:
    UPROPERTY(BlueprintReadWrite, Category = "Widgets")
    TObjectPtr<class UMainHallUserWidget> MainHallWidget;

    UPROPERTY(BlueprintReadWrite, Category = "Widgets")
    TObjectPtr<class UHelpUserWidget> HelpWidget; 
};
