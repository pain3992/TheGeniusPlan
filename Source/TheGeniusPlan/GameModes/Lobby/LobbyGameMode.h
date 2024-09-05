// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGameModeBase.h"
#include "LobbyGameMode.generated.h"

UCLASS()
class THEGENIUSPLAN_API ALobbyGameMode : public ADefaultGameMode
{
	GENERATED_BODY()
public:
	ALobbyGameMode();
	virtual void Logout(AController* Exiting) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	void TravelNewLevel();

	FTimerHandle GameModeTimerHandle;

	UPROPERTY()
	TSubclassOf<class AAAFGameModeBase> StartGameMode;
};
