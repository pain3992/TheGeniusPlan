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

    UPROPERTY(BlueprintReadWrite, Category = "PlayerData")
    FString LoginID;

    int32 GetPlayerScore() const;
    void SetPlayerScore(int32 NewScore);

    void AddScore(int32 Amount);

    virtual void OnRep_Score() override;

    UPROPERTY(ReplicatedUsing = OnRep_GarnetCount, BlueprintReadOnly, Category = "Garnet")
    int GarnetCount;

    UFUNCTION()
    void OnRep_GarnetCount();
   
    void AddGarnetCount(int32 GarnetAmount);

    int32 GetGarnetCount() const;
    void SetGarnetCount(int32 NewGarnetCount);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;
};
