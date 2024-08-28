// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFSelectWidget.h"
#include "Components/Button.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "Components/TextBlock.h"
#include "TheGeniusPlan/GameModes/GeniusGameInstance.h"

void UAAFSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(SelectedAbundance)
	{
		SelectedAbundance->SetIsEnabled(true);
		SelectedAbundance->OnClicked.AddDynamic(this, &UAAFSelectWidget::ClickedAbundance);
	}

	if(SelectedFamine)
	{
		SelectedFamine->SetIsEnabled(true);
		SelectedFamine->OnClicked.AddDynamic(this, &UAAFSelectWidget::ClickedFamine);

	}

}

void UAAFSelectWidget::ClickedAbundance()
{
	AAAFPlayerState* PlayerState = Cast<AAAFPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);

	if(PlayerState)
	{
		UE_LOG(LogTemp, Error, TEXT("ClickedAbundance"));
		PlayerState->ChangeLand(ESelectedLand::AbundanceLand);
		UGeniusGameInstance* GameInstance = Cast<UGeniusGameInstance>(GetGameInstance());
		GameInstance->GI_SelectedLand = ESelectedLand::AbundanceLand;
	}

	SelectedAbundance->SetVisibility(ESlateVisibility::Collapsed);
	SelectedFamine->SetVisibility(ESlateVisibility::Collapsed);

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

}

void UAAFSelectWidget::ClickedFamine()
{
	AAAFPlayerState* PlayerState = Cast<AAAFPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);

	if (PlayerState)
	{
		UE_LOG(LogTemp, Error, TEXT("ClickedFamine"));
		PlayerState->ChangeLand(ESelectedLand::FamineLand);
		UGeniusGameInstance* GameInstance = Cast<UGeniusGameInstance>(GetGameInstance());
		GameInstance->GI_SelectedLand = ESelectedLand::FamineLand;
	}
	
	SelectedAbundance->SetVisibility(ESlateVisibility::Collapsed);
	SelectedFamine->SetVisibility(ESlateVisibility::Collapsed);

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
}

void UAAFSelectWidget::SetTimer(float Time)
{
	FText TextTime = FText::AsNumber((int)Time);
	Timer->SetText(TextTime);
}
