// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLobbyPlayerController.h"
#include "TheGeniusPlan/Widget/GameLobbyWidget.h"
#include "TheGeniusPlan/GameModes/LobbyGameState.h"

void AGameLobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	BindDispatcher();
	CreateLobbyWidget();

}

AGameLobbyPlayerController::AGameLobbyPlayerController()
{
	static ConstructorHelpers::FClassFinder<UGameLobbyWidget>Lobby(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/Lobby/WG_LobbyWidget.WG_LobbyWidget_C'"));

	if (Lobby.Succeeded())
	{
		GameLobbyWidgetClass = Lobby.Class;
	}

	GameLobbyWidget = nullptr;
}

void AGameLobbyPlayerController::ChangePlayerCount(int32 NewNumber)
{
	if (GameLobbyWidget)
	{
		GameLobbyWidget->ChangePlayerCount(NewNumber);
	}
}

void AGameLobbyPlayerController::BindDispatcher()
{
	ALobbyGameState* LobbyGameState = Cast<ALobbyGameState>(GetWorld()->GetGameState());

	if (LobbyGameState)
	{
		LobbyGameState->PlayerCountDispatcher.AddDynamic(this, &AGameLobbyPlayerController::ChangePlayerCount);
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(StateTimer, this, &AGameLobbyPlayerController::BindDispatcher, 0.1f, false);

}

void AGameLobbyPlayerController::CreateLobbyWidget_Implementation()
{
	check(GameLobbyWidgetClass)

	if (GameLobbyWidget == nullptr)
	{
		GameLobbyWidget = CreateWidget<UGameLobbyWidget>(GetWorld(), GameLobbyWidgetClass);
		GameLobbyWidget->AddToViewport();
	}
	else
	{
		if (GameLobbyWidget->IsInViewport())
		{

		}
		else
		{
			GameLobbyWidget->AddToViewport();
		}
	}
}
