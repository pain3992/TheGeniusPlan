// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/Entry/LobbyWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "TheGeniusPlan/Characters/EntryPawn.h"
#include "TheGeniusPlan/GameModes/GeniusGameInstance.h"
#include "TheGeniusPlan/HUD/EntryHUD.h"
#include "TheGeniusPlan/Player/EntryPlayerController.h"

void ULobbyWidget::NativeConstruct()
{
	UE_LOG(LogTemp, Log, TEXT("LobbyWidget NativeConstruct"));
	Super::NativeConstruct();
	
	if (UGeniusGameInstance* GI = Cast<UGeniusGameInstance>(GetWorld()->GetGameInstance()))
	{
		GI->OnLoginInfoUpdated.AddDynamic(this, &ULobbyWidget::UpdateLoginInfo);  // Delegate 구독
	}
	
	if(ButtonLeft)
	{
		ButtonLeft->OnClicked.AddDynamic(this, &ULobbyWidget::ChangeCharacterMesh);
	}
	if(ButtonRight)
	{
		ButtonRight->OnClicked.AddDynamic(this, &ULobbyWidget::ChangeCharacterMesh);
	}
	if (ButtonQuit)
	{
		ButtonQuit->OnClicked.AddDynamic(this, &ULobbyWidget::ClickedQuit);
	}
	if (ButtonLogout)
	{
		ButtonLogout->OnClicked.AddDynamic(this, &ULobbyWidget::ClickedLogout);
	}
	if (ButtonOption)
	{
		ButtonOption->OnClicked.AddDynamic(this, &ULobbyWidget::ClickedOption);
	}
	if (ButtonServerJoin)
	{
		ButtonServerJoin->OnClicked.AddDynamic(this, &ULobbyWidget::ClickedJoinServer);
	}
	if (ButtonServerCreate)
	{
		ButtonServerCreate->OnClicked.AddDynamic(this, &ULobbyWidget::ClickedCreate);
	}
	
	// GameInstance에서 LoginInfo를 가져와
	// TextProfileName에 값을 설정한다
	if (UGeniusGameInstance* GI = Cast<UGeniusGameInstance>(GetWorld()->GetGameInstance()))
	{
		UE_LOG(LogTemp, Log, TEXT("LoginInfo!!: %s"), *GI->LoginInfo.UserName);
		if (GI->LoginInfo.bIsLoggedIn)
		{
			TextProfileName->SetText(FText::FromString(GI->LoginInfo.UserName));
		}
	}
}

void ULobbyWidget::UpdateLoginInfo(const FLoginInfo& LoginInfo)
{
	// LoginInfo가 갱신되면 TextProfileName도 갱신
	if (LoginInfo.bIsLoggedIn)
	{
		TextProfileName->SetText(FText::FromString(LoginInfo.UserName));
	}
}

void ULobbyWidget::ChangeCharacterMesh()
{
	if (AEntryPlayerController* Controller = Cast<AEntryPlayerController>(EntryHUD->GetOwner()))
	{
		if(AEntryPawn* Pawn = Cast<AEntryPawn>(Controller->GetPawn()))
		{
			Pawn->ChangeMesh();
		}
	}
}

void ULobbyWidget::ClickedJoinServer()
{
	FString ServerAddress = TEXT("127.0.0.1");
	GetWorld()->GetFirstPlayerController()->ClientTravel(ServerAddress, ETravelType::TRAVEL_Absolute);
	//UGameplayStatics::OpenLevel(GetWorld(), FName("LobbyLevel"), true, "127.0.0.1");
	
}

void ULobbyWidget::ClickedQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void ULobbyWidget::ClickedLogout()
{
	EntryHUD->ShowWidget(EntryWidgetType::LoginWidget);
}

void ULobbyWidget::ClickedOption()
{
	EntryHUD->ShowWidget(EntryWidgetType::OptionWidget);
}

void ULobbyWidget::ClickedCreate()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("LobbyLevel"), true, "listen");
}
