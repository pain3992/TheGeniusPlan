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
	if (ButtonRemoteServerJoin)
	{
		ButtonRemoteServerJoin->OnClicked.AddDynamic(this, &ULobbyWidget::ClickedJoinRemoteServer);
	}
	if (ButtonServerCreate)
	{
		ButtonServerCreate->OnClicked.AddDynamic(this, &ULobbyWidget::ClickedCreate);
	}
}

void ULobbyWidget::UpdateLoginInfo(const FLoginInfo& LoginInfo)
{
	// LoginInfo가 갱신되면 프로필 정보 업데이트
	if (LoginInfo.bIsLoggedIn)
	{
		// 플레이어 닉네임
		TextProfileName->SetText(FText::FromString(LoginInfo.UserName));
		// 플레이어 전적
		TextProfileStatistics->SetText(FText::FromString(FString::FromInt(LoginInfo.TotalGame) + TEXT("전 ") + FString::FromInt(LoginInfo.TotalWin) + TEXT("승 (") + FString::FromInt(LoginInfo.WinRate) + TEXT("%)")));
		// 플레이어 랭킹
		TextProfileRanking->SetText(FText::FromString(FString::FromInt(LoginInfo.Rank) + TEXT("등/") + FString::FromInt(LoginInfo.RankPlayers) + TEXT("명")));
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
}

void ULobbyWidget::ClickedJoinRemoteServer()
{
	FString ServerAddress = TEXT("11.11.111.111:7777");
	GetWorld()->GetFirstPlayerController()->ClientTravel(ServerAddress, ETravelType::TRAVEL_Absolute);
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
