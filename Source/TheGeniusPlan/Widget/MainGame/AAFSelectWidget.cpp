// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFSelectWidget.h"
#include "Components/Button.h"
#include "TheGeniusPlan/PlayerState/AAFPlayerState.h"

void UAAFSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(SelectedAbundance)
	{
		SelectedAbundance->OnClicked.AddDynamic(this, &UAAFSelectWidget::ClickedAbundance);
	}

	if(SelectedFamine)
	{
		SelectedFamine->OnClicked.AddDynamic(this, &UAAFSelectWidget::ClickedFamine);

	}
}

void UAAFSelectWidget::ClickedAbundance()
{
	AAAFPlayerState* PlayerState = Cast<AAAFPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	if(PlayerState)
	{
		PlayerState->ChangeLand(ESelectedLand::AbundanceLand);
	}

}

void UAAFSelectWidget::ClickedFamine()
{
	AAAFPlayerState* PlayerState = Cast<AAAFPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	if (PlayerState)
	{
		PlayerState->ChangeLand(ESelectedLand::FamineLand);
	}
}
