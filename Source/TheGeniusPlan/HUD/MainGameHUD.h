// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainGameHUD.generated.h"


UENUM()
enum class MainGameWidgetType : uint8
{
	// Home 작업 예시 2 
    NONE UMETA(DisplayName = "NONE"),
    MainGameWidget UMETA(DisplayName = "MainGameWidget"),
    HelpWidget UMETA(DisplayName = "HelpWidget"),
    MAX UMETA(DisplayName = "MAX")
};

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AMainGameHUD : public AHUD
{
	GENERATED_BODY()

public:
    AMainGameHUD();

	virtual void BeginPlay() override;

    UFUNCTION()
    void ShowWidget(MainGameWidgetType type);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
    TSubclassOf<class UMainGameWidget> MainGameWidgetClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
    TSubclassOf<class UHelpUserWidget> HelpWidgetClass;

    // Function to set visibility of HelpWidget
    void SetHelpWidgetVisibility(ESlateVisibility Visibility);
    void ShowMouseCursor(bool bShowCursor);
   // void UpdateRankingList();

        // Public accessor for MainGameWidget
    UFUNCTION(BlueprintCallable, Category = "Widgets")
    UMainGameWidget* GetMainGameWidget() const { return MainGameWidget; }

    UPROPERTY(BlueprintReadWrite, Category = "Widgets")
    TObjectPtr<class UMainGameWidget> MainGameWidget;

    UFUNCTION()
    void CreateResultWidget(uint8 First, uint8 Seconds);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
    TSubclassOf<class UShowPlayerSeletedLandWidget> ShowLandWidgetClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
    TSubclassOf<class UAAFSelectWidget> SelectLandWidgetClass;

    UPROPERTY(BlueprintReadWrite, Category = "Widgets")
    TObjectPtr<class UShowPlayerSeletedLandWidget> ShowLandWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
    TObjectPtr<class UAAFSelectWidget> SelectLandWidget;


protected:
    UPROPERTY(BlueprintReadWrite, Category = "Widgets")
    TObjectPtr<class UHelpUserWidget> HelpWidget; 

};
