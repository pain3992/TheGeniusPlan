// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LobbyGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventDispatcher_PlayerCount, int32, PlayerNumber);


UCLASS()
class THEGENIUSPLAN_API ALobbyGameState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(ReplicatedUsing = OnReq_ChangeConunt);
	int32 PlayerCount;

	UFUNCTION()
	void IncrasePlayerCount();

	ALobbyGameState();

	UFUNCTION()
	void OnReq_ChangeConunt();

	UPROPERTY()
	FEventDispatcher_PlayerCount PlayerCountDispatcher;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void ChangePlayerCount(int32 NewNumber);

	
};
