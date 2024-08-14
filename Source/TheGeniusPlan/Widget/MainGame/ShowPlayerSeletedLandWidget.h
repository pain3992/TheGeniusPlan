// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShowPlayerSeletedLandWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UShowPlayerSeletedLandWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> ALand;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> FLand;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> Timer;

public:

	UFUNCTION()
	void SetTextBox(const uint8& AbundanceNumber,const uint8& FamineNumber);

	UFUNCTION()
	void SetTimer(float Time);

	
};
