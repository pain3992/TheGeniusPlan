// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AAFSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UAAFSelectWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> SelectedAbundance;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> SelectedFamine;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> Timer;

public:
	UFUNCTION()
	void ClickedAbundance();

	UFUNCTION()
	void ClickedFamine();

	UFUNCTION()
	void SetTimer(float Time);
	

};
