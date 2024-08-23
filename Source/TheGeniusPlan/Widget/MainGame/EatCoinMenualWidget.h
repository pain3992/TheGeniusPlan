// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EatCoinMenualWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UEatCoinMenualWidget : public UUserWidget
{
	GENERATED_BODY()
	

public: 

	UFUNCTION(BlueprintCallable, Category = "Countdown")
	void UpdateStartEatCoinCountdownDisplay(int32 CountdownTimeInSeconds);

protected:
	virtual void NativeConstruct() override;


private:
	FTimerHandle CountdownTimerHandle;
	int32 StartEatCoinCountdownTime;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_StartTimer;

};
