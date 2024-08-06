// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/OptionWidget.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TheGeniusPlan/GameModes/MainMenuHUD.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"
#include "AudioDevice.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"

void UOptionWidget::NativeConstruct()
{
	if(ButtonApply)
	{
		ButtonApply->OnClicked.AddDynamic(this, &UOptionWidget::ClickedApplyButton);
	}
	if (ButtonCansel)
	{
		ButtonCansel->OnClicked.AddDynamic(this, &UOptionWidget::ClickedCanselButton);
	}

	ResolutionComboBox->AddOption(TEXT("1920X1080"));
	ResolutionComboBox->AddOption(TEXT("1280X720"));
	ResolutionComboBox->AddOption(TEXT("800X600"));

	Usersetting = GEngine->GetGameUserSettings();
	SaveVolume = 1.0f;

}

void UOptionWidget::ClickedApplyButton()
{
	FString SelectedOption = ResolutionComboBox->GetSelectedOption();

	TArray<FString> SelectedParts;
	SelectedOption.ParseIntoArray(SelectedParts, TEXT("x"), true);

	if(SelectedParts.Num() == 2)
	{
		int Width = FCString::Atoi(*SelectedParts[0]);
		int Height = FCString::Atoi(*SelectedParts[1]);

		if(Width > 0 && Height > 0)
		{
			if(Usersetting)
			{
				Usersetting->SetScreenResolution(FIntPoint(Width, Height));
				Usersetting->ApplySettings(true);
				Usersetting->ConfirmVideoMode();
			}
		}
	}

	float Volume = SoundSlider->GetValue();
	float Gamma = BrightSlider->GetValue();

	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), nullptr, nullptr, Volume, 1.0f);
	GEngine->DisplayGamma = Gamma;

	SaveVolume = Volume;

	SetVisibility(ESlateVisibility::Collapsed);
}

void UOptionWidget::ClickedCanselButton()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UOptionWidget::LoadUserSetting()
{
	float Gamma = GEngine->GetDisplayGamma();
	BrightSlider->SetValue(Gamma);
	SoundSlider->SetValue(SaveVolume);
	
}
