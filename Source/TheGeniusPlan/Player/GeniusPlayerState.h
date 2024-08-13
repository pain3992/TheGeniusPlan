// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// DECLARE_DYNAMIC_MULTICAST_DELEGATE_


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

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
