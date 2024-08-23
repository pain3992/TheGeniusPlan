// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionWidget.generated.h"


UCLASS()
class THEGENIUSPLAN_API UOptionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ClickedApplyButton();

	UFUNCTION()
	void ClickedCanselButton();

	UFUNCTION()
	void LoadUserSetting();

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	TObjectPtr<class AEntryHUD> EntryHUD;


protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class USlider> SoundSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class USlider> BrightSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonApply;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonCansel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UComboBoxString> ResolutionComboBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting")
	TObjectPtr<class UGameUserSettings> Usersetting;

	float SaveVolume;
};
