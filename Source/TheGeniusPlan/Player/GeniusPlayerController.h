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

	virtual void BeginPlay() override;

    UFUNCTION()
    void BindDispatcher();

 //   UPROPERTY()
 //   FTimerHandle TimerHandle;

    UPROPERTY()
    FTimerHandle TimerHandletwo;

 //   UPROPERTY()
 //   FTimerHandle TimerHandlePC;

    UFUNCTION()
    void GameStepChange(EGameStep NewStep);

    virtual void Tick(float DeltaSeconds) override;
    
    UPROPERTY()
    TObjectPtr<AAAFGameState> GameState;

 //   UFUNCTION()
 //   void RequestServerChangeStep();

    UFUNCTION()
    void MoveActor();

    UFUNCTION(Server, Reliable)
    void Server_MoveActor();

    UFUNCTION(NetMulticast, Reliable)
    void Client_MoveActor();

    UPROPERTY()
    TObjectPtr<class AAAFPlayerState> CastPlayerState;

    UFUNCTION()
    void RequestGameStateFunction();

    UFUNCTION(Server, Reliable)
    void ResponseGameStateFunction();

 //   UFUNCTION()
 //   void Req_GameStepChange();

 //   UFUNCTION(Server, Reliable)
 //   void Server_GameStepChange();
};
