// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFSelectWidget.h"
#include "Components/Button.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"

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
	}

	RemoveFromParent();

}

void UAAFSelectWidget::ClickedFamine()
{
	AAAFPlayerState* PlayerState = Cast<AAAFPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);

	if (PlayerState)
	{
		UE_LOG(LogTemp, Error, TEXT("ClickedFamine"));
		PlayerState->ChangeLand(ESelectedLand::FamineLand);
	}

	RemoveFromParent();
}
