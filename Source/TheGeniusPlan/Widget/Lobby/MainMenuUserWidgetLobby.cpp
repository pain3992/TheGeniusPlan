// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUserWidgetLobby.h"
#include "TheGeniusPlan/GameModes/Lobby/MainMenuHUD.h"
#include "Components/Button.h"
#include "TheGeniusPlan/Characters/MainMenuPawn.h"
#include "TheGeniusPlan/GameModes/Lobby/MainMenuPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuUserWidgetLobby::NativeConstruct()
{
	Super::NativeConstruct();

	if(ButtonLeft)
	{
		ButtonLeft->OnClicked.AddDynamic(this, &UMainMenuUserWidgetLobby::ChangeCharacterMesh);
	}
	if(ButtonRight)
	{
		ButtonRight->OnClicked.AddDynamic(this, &UMainMenuUserWidgetLobby::ChangeCharacterMesh);
	}
	if (ButtonQuit)
	{
		ButtonQuit->OnClicked.AddDynamic(this, &UMainMenuUserWidgetLobby::ClickedQuit);
	}
	if (ButtonLogout)
	{
		ButtonLogout->OnClicked.AddDynamic(this, &UMainMenuUserWidgetLobby::ClickedLogout);
	}
	if (ButtonOption)
	{
		ButtonOption->OnClicked.AddDynamic(this, &UMainMenuUserWidgetLobby::ClickedOption);
	}
	if (ButtonServerJoin)
	{
		ButtonServerJoin->OnClicked.AddDynamic(this, &UMainMenuUserWidgetLobby::ClickedJoinServer);
	}

}

void UMainMenuUserWidgetLobby::ChangeCharacterMesh()
{

	AMainMenuPlayerController* Controller = Cast<AMainMenuPlayerController>(LobbyMenuHUD->GetOwner());

	if (Controller)
	{
		AMainMenuPawn* Pawn = Cast<AMainMenuPawn>(Controller->GetPawn());
		if(Pawn)
		{
			Pawn->ChangeMesh();
		}
	}
}

void UMainMenuUserWidgetLobby::ClickedJoinServer()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Lobby")), true, FString(TEXT("127.0.0.1:7777")));
}

void UMainMenuUserWidgetLobby::ClickedQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UMainMenuUserWidgetLobby::ClickedLogout()
{
	LobbyMenuHUD->ShowWidget(WidgetType::LoginWidget);
}

void UMainMenuUserWidgetLobby::ClickedOption()
{
	LobbyMenuHUD->ShowWidget(WidgetType::OptionWidget);
}
