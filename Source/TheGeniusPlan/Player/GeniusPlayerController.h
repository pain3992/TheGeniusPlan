// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../GameModes/MainGame/AAFGameState.h"
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
	TSubclassOf<class UShowPlayerSeletedLandWidget> SelectResultWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UAAFSelectWidget> SelectLandWidgetClass;

    UFUNCTION()
    void CreateVoteWidget();

	virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, Category = "Widgets")
    TObjectPtr<class UShowPlayerSeletedLandWidget> SelectResultWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
    TObjectPtr<class UAAFSelectWidget> SelectLandWidget;

    UFUNCTION()
    void BindDispatcher();

    UPROPERTY()
    FTimerHandle TimerHandle;

    UPROPERTY()
    FTimerHandle TimerHandletwo;

    UFUNCTION()
    void GameStepChange(EGameStep NewStep);

    UFUNCTION()
    void CreateResultWidget(uint8 FNumber, uint8 SNumber);

    UFUNCTION()
    void RemoveResultWidget();

    uint8 AbundanceLand;

    uint8 FamineLand;

    UFUNCTION()
    void CheckPlayerAllSelected();

    UFUNCTION(Server, Reliable)
    void RequestChangetStepOnServer(EGameStep NewStep, uint8 FirstLand, uint8 SecondsLand);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
    TSubclassOf<class UTimerWidget> TimerWidgetClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
    TObjectPtr<class UTimerWidget> TimerWidget;

    UFUNCTION(Client, Reliable)
    void CreateTimerWidget();

    UFUNCTION()
    void UpdateTimerWidget(double NewTime);

    virtual void Tick(float DeltaSeconds) override;
    
    UPROPERTY()
    TObjectPtr<AAAFGameState> GameState;

    bool IsCreateWidget;

    FTimerHandle TimerHandlePC;

    UFUNCTION()
    void RequestServerChangeStep();

    UFUNCTION()
    void MoveActor();
};
