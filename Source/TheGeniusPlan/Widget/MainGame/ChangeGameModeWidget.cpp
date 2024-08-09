#include "TheGeniusPlan/Widget/MainGame/ChangeGameModeWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameModeBase.h"

void UChangeGameModeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ChangeGameModeButton)
	{
		ChangeGameModeButton->OnClicked.AddDynamic(this, &UChangeGameModeWidget::OnChangeGameModeButtonClicked);
	}
}

void UChangeGameModeWidget::OnChangeGameModeButtonClicked()
{
	AGameModeBase *GameMode = UGameplayStatics::GetGameMode(GetWorld());
	if (AMainGameModeBase *MainGameMode = Cast<AMainGameModeBase>(GameMode))
	{
		UE_LOG(LogTemp, Warning, TEXT("OnChangeGameModeButtonClicked"));
		MainGameMode->SelectNextGameMode();
	}
}
