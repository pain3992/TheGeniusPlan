// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GeniusPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AGeniusPlayerState : public APlayerState
{
	GENERATED_BODY()


public:
    UPROPERTY(Replicated, BlueprintReadWrite, Category = "PlayerData")
    FString PlayerName;

    int32 GetPlayerScore() const;
    void SetPlayerScore(int32 NewScore);

    void AddScore(int32 Amount);

    virtual void OnRep_Score() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
