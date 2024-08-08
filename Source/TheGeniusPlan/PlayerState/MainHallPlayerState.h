// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainHallPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AMainHallPlayerState : public APlayerState
{
	GENERATED_BODY()


public:
    UPROPERTY(Replicated, BlueprintReadWrite, Category = "PlayerData")
    FString PlayerName;

    int32 GetPlayerScore() const;
    void SetPlayerScore(int32 NewScore);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
