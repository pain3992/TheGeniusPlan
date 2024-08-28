// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/GameModes/Lobby/LobbyGameMode.h"
#include "TheGeniusPlan/Widget/GameLobbyWidget.h"
#include "LobbyGameState.h"
#include "TheGeniusPlan/Player/GameLobbyPlayerController.h"
#include "TheGeniusPlan/HUD/MainGameLobbyHUD.h"
#include "TheGeniusPlan/GameModes/MainGame/AAFGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ALobbyGameMode::ALobbyGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C'"));
	static ConstructorHelpers::FClassFinder<AAAFGameModeBase> NewGameModeClass(TEXT("/Script/CoreUObject.Class'/Script/TheGeniusPlan.AAFGameModeBase'"));

	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	if(NewGameModeClass.Succeeded())
	{
		StartGameMode = NewGameModeClass.Class;
	}


	GameStateClass = ALobbyGameState::StaticClass();
	PlayerControllerClass = AGameLobbyPlayerController::StaticClass();
	HUDClass = AMainGameLobbyHUD::StaticClass();

}

void ALobbyGameMode::Logout(AController* Exiting)
{
	// UE_LOG(LogTemp, Warning, TEXT("Logout!!"));
	Super::Logout(Exiting);
}

void ALobbyGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	// UE_LOG(LogTemp, Warning, TEXT("PostLogin!!"));
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	int32 CurrentPlayerCount = GetNumPlayers();

	if(CurrentPlayerCount > 0)
	{
		ALobbyGameState* LobbyGameState = Cast<ALobbyGameState>(GameState);
		LobbyGameState->ChangePlayerCount(CurrentPlayerCount);

		if(CurrentPlayerCount == 3)
		{
			UE_LOG(LogTemp, Error, TEXT("All Player Join"));

			GetWorld()->GetTimerManager().SetTimer(GameModeTimerHandle, this, &ALobbyGameMode::TravelNewLevel, 10.0f, false);
		}
	}
}

void ALobbyGameMode::TravelNewLevel()
{
	FString TravelURL = FString::Printf(TEXT("/Game/Levels/MainLevel?game=/Script/TheGeniusPlan.MainGameModeBase"));
	GetWorld()->ServerTravel(TravelURL);
}

