// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameLobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AGameLobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	AGameLobbyPlayerController();

	UPROPERTY()
	TSubclassOf<class UGameLobbyWidget> GameLobbyWidgetClass;

	UPROPERTY()
	TObjectPtr<class UGameLobbyWidget> GameLobbyWidget;

	UFUNCTION()
	void ChangePlayerCount(int32 NewNumber);

	UFUNCTION()
	void BindDispatcher();

	UPROPERTY()
	FTimerHandle StateTimer;

	UFUNCTION(Client, Reliable)
	void CreateLobbyWidget();

};
