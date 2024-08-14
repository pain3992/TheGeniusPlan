// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeniusPlayerState.h"
#include "AAFPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventDispatcher_AllPlayerSelected);

UENUM()
enum class ESelectedLand : uint8
{
	None UMETA(Displayname = "None"),
	AbundanceLand UMETA(Displayname = "Abundance"),
	FamineLand UMETA(Displayname = "FamineLand"),

};

UCLASS()
class THEGENIUSPLAN_API AAAFPlayerState : public AGeniusPlayerState
{
	GENERATED_BODY()

protected:

public:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FEventDispatcher_AllPlayerSelected AllPlayerSelected;

	UPROPERTY(ReplicatedUsing = OnReq_ChangeLand)
	ESelectedLand SelectedLand;

	AAAFPlayerState();

	UFUNCTION()
	void OnReq_ChangeLand();

	UFUNCTION(Server, Reliable)
	void ChangeLand(ESelectedLand Type);

	UFUNCTION()
	void ResetLand();

	UFUNCTION()
	ESelectedLand GetSelectedLand();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
