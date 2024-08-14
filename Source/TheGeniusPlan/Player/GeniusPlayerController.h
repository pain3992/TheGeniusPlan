// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GeniusPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AGeniusPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    AGeniusPlayerController();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UShowPlayerSeletedLandWidget> ShowLandWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UAAFSelectWidget> SelectLandWidgetClass;

	UFUNCTION(NetMulticast, Reliable)
	void SetDrawResultWidget(uint8 firstNumber, uint8 SecondsNumber);

    UFUNCTION()
    void CreateVoteWidget();

	virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, Category = "Widgets")
    TObjectPtr<class UShowPlayerSeletedLandWidget> ShowLandWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
    TObjectPtr<class UAAFSelectWidget> SelectLandWidget;

    UFUNCTION()
    void PlayerStateBind();

    UPROPERTY()
    FTimerHandle TimerHandle;

    UPROPERTY()
    FTimerHandle TimerHandletwo;

    UPROPERTY()
    float Timer;

    UFUNCTION()
    void AllPlayerSelectedCheck();

    UFUNCTION(Server, Reliable)
    void Req_PlayerCreateResultWidget(uint8 FNumber, uint8 SNumber);

    UFUNCTION()
    void RemoveResultWidget();

    UFUNCTION()
    void SetTimerWidget();

    UPROPERTY()
    uint8 AbundanceLand;

    UPROPERTY()
    uint8 FamineLand;
};
