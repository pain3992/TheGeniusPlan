#include "TheGeniusPlan/HUD/EntryHUD.h"

#include "TheGeniusPlan/Widget/Entry/EntryWidget.h"
#include "TheGeniusPlan/Widget/Entry/LobbyWidget.h"
#include "TheGeniusPlan/Widget/Entry/LoginWidget.h"
#include "TheGeniusPlan/Widget/Entry/OptionWidget.h"
#include "TheGeniusPlan/Widget/Entry/SignupWidget.h"

AEntryHUD::AEntryHUD()
{
	static ConstructorHelpers::FClassFinder<ULoginWidget> CLoginWidget(TEXT("/Game/UI/Widget/Entry/WBP_Login.WBP_Login_C"));
	static ConstructorHelpers::FClassFinder<UEntryWidget> CEntryWidget(TEXT("/Game/UI/Widget/Entry/WBP_Entry.WBP_Entry_C"));
	static ConstructorHelpers::FClassFinder<ULobbyWidget> CLobbyWidget(TEXT("/Game/UI/Widget/Lobby/WBP_Lobby.WBP_Lobby_C"));
	static ConstructorHelpers::FClassFinder<UUserWidget> CLoadingWidget(TEXT("/Game/UI/Widget/WBP_Loading.WBP_Loading_C"));
	static ConstructorHelpers::FClassFinder<USignupWidget> CSignupWidget(TEXT("/Game/UI/Widget/Entry/WBP_Signup.WBP_Signup_C"));
	static ConstructorHelpers::FClassFinder<UOptionWidget> COptionWidget(TEXT("/Game/UI/Widget/Entry/WBP_GameOption.WBP_GameOption_C"));

	if(CLoginWidget.Succeeded() && CEntryWidget.Succeeded() && CLobbyWidget.Succeeded() && CLoadingWidget.Succeeded() && CSignupWidget.Succeeded() && COptionWidget.Succeeded())
	{
		LoginWidgetClass = CLoginWidget.Class;
		EntryWidgetClass = CEntryWidget.Class;
		LobbyWidgetClass = CLobbyWidget.Class;
		LoadingWidgetClass = CLoadingWidget.Class;
		SignupWidgetClass = CSignupWidget.Class;
		OptionWidgetClass = COptionWidget.Class;
	}
}

void AEntryHUD::BeginPlay()
{
	Super::BeginPlay();

	check(LoginWidgetClass)
	check(SignupWidgetClass)
	check(EntryWidgetClass)
	check(OptionWidgetClass)
	check(LobbyWidgetClass)
	check(LoadingWidgetClass)

	LoginWidget = Cast<ULoginWidget>(CreateWidget(GetWorld(), LoginWidgetClass, TEXT("LoginMenuHUD")));
	EntryWidget = Cast<UEntryWidget>(CreateWidget(GetWorld(), EntryWidgetClass, TEXT("GameStartMenuHUD")));
	LobbyWidget = Cast<ULobbyWidget>(CreateWidget(GetWorld(), LobbyWidgetClass, TEXT("LobbyMenuHUD")));
	LoadingWidget = Cast<UUserWidget>(CreateWidget(GetWorld(), LoadingWidgetClass));
	SignupWidget = Cast<USignupWidget>(CreateWidget(GetWorld(), SignupWidgetClass, TEXT("SignupMenuHUD")));
	OptionWidget = Cast<UOptionWidget>(CreateWidget(GetWorld(), OptionWidgetClass, TEXT("OptionMenuHUD")));

	if (LoginWidget)
	{
		LoginWidget->EntryHUD= this;
		LoginWidget->AddToViewport();
	}

	if (EntryWidget)
	{
		EntryWidget->EntryHUD = this;
		EntryWidget->AddToViewport();
	}

	if (LobbyWidget)
	{
		LobbyWidget->EntryHUD = this;
		LobbyWidget->AddToViewport();
	}

	if(LoadingWidget)
	{
		LoadingWidget->AddToViewport();
		LoadingWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (SignupWidget)
	{
		SignupWidget->EntryHUD = this;
		SignupWidget->AddToViewport();
	}

	if (OptionWidget)
	{
		OptionWidget->EntryHUD = this;
		OptionWidget->AddToViewport();
	}

	// 초기시작 위젯
	ShowWidget(EntryWidgetType::LoginWidget);
}

void AEntryHUD::ShowWidget(EntryWidgetType type) const
{
	switch (type)
	{
	case EntryWidgetType::NONE:
		break;
	case EntryWidgetType::LoginWidget:
		LoginWidget->SetVisibility(ESlateVisibility::Visible);
		EntryWidget->SetVisibility(ESlateVisibility::Collapsed);
		LobbyWidget->SetVisibility(ESlateVisibility::Collapsed);
		SignupWidget->SetVisibility(ESlateVisibility::Collapsed);
		OptionWidget->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EntryWidgetType::EntryWidget:
		LoginWidget->SetVisibility(ESlateVisibility::Collapsed);
		EntryWidget->SetVisibility(ESlateVisibility::Visible);
		LobbyWidget->SetVisibility(ESlateVisibility::Collapsed);
		SignupWidget->SetVisibility(ESlateVisibility::Collapsed);
		OptionWidget->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EntryWidgetType::LobbyWidget:
		LoginWidget->SetVisibility(ESlateVisibility::Collapsed);
		EntryWidget->SetVisibility(ESlateVisibility::Collapsed);
		LobbyWidget->SetVisibility(ESlateVisibility::Visible);
		SignupWidget->SetVisibility(ESlateVisibility::Collapsed);
		OptionWidget->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EntryWidgetType::OptionWidget:
		OptionWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case EntryWidgetType::SignupWidget:
		SignupWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case EntryWidgetType::MAX:
		break;
	default:
		break;
	}
}
