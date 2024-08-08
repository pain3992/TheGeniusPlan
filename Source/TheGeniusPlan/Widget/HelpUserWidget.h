// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HelpUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UHelpUserWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Back;

public:
	void SetHUD(class AMainHallHUD* InHUD);

private:
	UFUNCTION()
	void OnBackButtonClicked();

	AMainHallHUD* HUD;

};
