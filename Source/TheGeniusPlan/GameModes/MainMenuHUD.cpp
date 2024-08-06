#include "TheGeniusPlan/GameModes/MainMenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "TheGeniusPlan/Widget/MainMenuUserWidget.h"
#include "TheGeniusPlan/Widget/MainMenuUserWidgetOption.h"
#include "TheGeniusPlan/Widget/MainMenuUserWidgetLobby.h"
#include "TheGeniusPlan/Widget/OptionWidget.h"
#include "TheGeniusPlan/Widget/SignupWidget.h"

AMainMenuHUD::AMainMenuHUD()
{
	static ConstructorHelpers::FClassFinder<UMainMenuUserWidget> CLoginWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Mainmenu/Widget/WG_MainMenuLogin.WG_MainMenuLogin_C'"));
	static ConstructorHelpers::FClassFinder<UMainMenuUserWidgetOption> CGameStartWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Mainmenu/Widget/WG_MainMenuGameStart.WG_MainMenuGameStart_C'"));
	static ConstructorHelpers::FClassFinder<UMainMenuUserWidgetLobby> CLobbyWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Mainmenu/Widget/WG_MainMenuLobbyWidget.WG_MainMenuLobbyWidget_C'"));
	static ConstructorHelpers::FClassFinder<UUserWidget> CLoadingWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Mainmenu/Widget/WG_Loading.WG_Loading_C'"));
	static ConstructorHelpers::FClassFinder<USignupWidget> CSignupWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Mainmenu/Widget/WG_Signup.WG_Signup_C'"));
	static ConstructorHelpers::FClassFinder<UOptionWidget> COptionWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Mainmenu/Widget/WG_OptionWidget.WG_OptionWidget_C'"));

	if(CLoginWidget.Succeeded() && CGameStartWidget.Succeeded() && CLobbyWidget.Succeeded() && CLoadingWidget.Succeeded() && CSignupWidget.Succeeded() && COptionWidget.Succeeded())
	{
		LoginWidgetClass = CLoginWidget.Class;
		GameStartWidgetClass = CGameStartWidget.Class;
		LobbyWidgetClass = CLobbyWidget.Class;
		LoadingWidgetClass = CLoadingWidget.Class;
		SignupWidgetClass = CSignupWidget.Class;
		OptionWidgetClass = COptionWidget.Class;
	}

}

void AMainMenuHUD::ShowWidget(WidgetType type)
{
	switch (type)
	{
	case WidgetType::NONE:
		break;
	case WidgetType::LoginWidget:
		LoginWidget->SetVisibility(ESlateVisibility::Visible);
		GameStartWidget->SetVisibility(ESlateVisibility::Collapsed);
		LobbyWidget->SetVisibility(ESlateVisibility::Collapsed);
		SignupWidget->SetVisibility(ESlateVisibility::Collapsed);
		OptionWidget->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case WidgetType::StartWidget:
		LoginWidget->SetVisibility(ESlateVisibility::Collapsed);
		GameStartWidget->SetVisibility(ESlateVisibility::Visible);
		LobbyWidget->SetVisibility(ESlateVisibility::Collapsed);
		SignupWidget->SetVisibility(ESlateVisibility::Collapsed);
		OptionWidget->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case WidgetType::LobbyWidget:
		LoginWidget->SetVisibility(ESlateVisibility::Collapsed);
		GameStartWidget->SetVisibility(ESlateVisibility::Collapsed);
		LobbyWidget->SetVisibility(ESlateVisibility::Visible);
		SignupWidget->SetVisibility(ESlateVisibility::Collapsed);
		OptionWidget->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case WidgetType::OptionWidget:
		OptionWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case WidgetType::SignupWidget:
		SignupWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case WidgetType::MAX:
		break;
	default:
		break;
	}

}


void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	check(LoginWidgetClass)
	check(GameStartWidgetClass)
	check(LobbyWidgetClass)
	check(LoadingWidgetClass)
	check(OptionWidgetClass)
	check(SignupWidgetClass)

	LoginWidget = Cast<UMainMenuUserWidget>(CreateWidget(GetWorld(), LoginWidgetClass, TEXT("LoginMenuHUD")));

	if (LoginWidget)
	{
		LoginWidget->LoginMenuHUD = this;
		LoginWidget->AddToViewport();
	}

	GameStartWidget = Cast<UMainMenuUserWidgetOption>(CreateWidget(GetWorld(), GameStartWidgetClass, TEXT("GameStartMenuHUD")));

	if (GameStartWidget)
	{
		GameStartWidget->GameStartMenuHUD = this;
		GameStartWidget->AddToViewport();
	}

	LobbyWidget = Cast<UMainMenuUserWidgetLobby>(CreateWidget(GetWorld(), LobbyWidgetClass, TEXT("LobbyMenuHUD")));

	if (LobbyWidget)
	{
		LobbyWidget->LobbyMenuHUD = this;
		LobbyWidget->AddToViewport();
	}

	LoadingWidget = Cast<UUserWidget>(CreateWidget(GetWorld(), LoadingWidgetClass));

	if(LoadingWidget)
	{
		LoadingWidget->AddToViewport();
		LoadingWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	SignupWidget = Cast<USignupWidget>(CreateWidget(GetWorld(), SignupWidgetClass, TEXT("SignupMenuHUD")));

	if (SignupWidget)
	{
		SignupWidget->SignupMenuHUD = this;
		SignupWidget->AddToViewport();
	}

	OptionWidget = Cast<UOptionWidget>(CreateWidget(GetWorld(), OptionWidgetClass, TEXT("OptionMenuHUD")));

	if (OptionWidget)
	{
		OptionWidget->OptionMenuHUD = this;
		OptionWidget->AddToViewport();
	}

	ShowWidget(WidgetType::LoginWidget);

}


