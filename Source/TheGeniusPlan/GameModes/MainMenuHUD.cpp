#include "TheGeniusPlan/GameModes/MainMenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "TheGeniusPlan/Widget/MainMenuUserWidget.h"

AMainMenuHUD::AMainMenuHUD()
{
	static ConstructorHelpers::FClassFinder<UMainMenuUserWidget> WG_MainMenuWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Mainmenu/Widget/WG_MainMenu.WG_MainMenu_C'"));

	if (WG_MainMenuWidget.Succeeded())
	{
		MainMenuWidgetClass = WG_MainMenuWidget.Class;
	}
}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	MainMenuWidget = Cast<UMainMenuUserWidget>(CreateWidget(GetWorld(), MainMenuWidgetClass));

	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();
	}
	

}


