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

public:
	// 가시성 변경 시 호출되는 함수
	virtual void SetVisibility(ESlateVisibility InVisibility) override;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Back;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Hint;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Award;


public:
	void SetHUD(class AMainGameHUD* InHUD);

	UFUNCTION(BlueprintCallable, Category = "Hint")
	void SetHintText(const FString& NewText);

	UFUNCTION(BlueprintCallable, Category = "Hint")
	void SetAwardText(const FString& NewText);

	void UpdateTextBaseOnLevel();

private:
	UFUNCTION()
	void OnBackButtonClicked();

	AMainGameHUD* HUD;

};
