// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AAFGameEndWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UAAFGameEndWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Winner;
	
	UFUNCTION()
	void SetTextBlock(FText& NewWinner);
};
