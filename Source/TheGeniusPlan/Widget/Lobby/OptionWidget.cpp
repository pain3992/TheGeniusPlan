// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/Lobby/OptionWidget.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
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

	LoadUserSetting();
}

void UOptionWidget::ClickedApplyButton()
{
	FString SelectedOption = ResolutionComboBox->GetSelectedOption();

	TArray<FString> SelectedParts;
	SelectedOption.ParseIntoArray(SelectedParts, TEXT("X"), true);

	if(SelectedParts.Num() == 2)
	{
		int Width = FCString::Atoi(*SelectedParts[0]);
		int Height = FCString::Atoi(*SelectedParts[1]);

		UE_LOG(LogTemp, Warning, TEXT("Width, Height Setting"));

		if(Width > 0 && Height > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Width, Height Not zero"));

			if(Usersetting)
			{
				Usersetting->SetScreenResolution(FIntPoint(Width, Height));
				Usersetting->ApplySettings(true);
				Usersetting->ConfirmVideoMode();
				UE_LOG(LogTemp, Warning, TEXT("Setting Video"));

			}
		}
	}

	float Volume = SoundSlider->GetValue();
	float Gamma = BrightSlider->GetValue();
	float SettingGamma = FMath::Lerp(1.0f, 3.0f, Gamma);

	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), nullptr, nullptr, Volume, 1.0f);
	GEngine->DisplayGamma = SettingGamma;

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
	float SettingGamma = FMath::Lerp(0.0f, 1.0f, Gamma);

	BrightSlider->SetValue(SettingGamma);
	SoundSlider->SetValue(SaveVolume);
}
