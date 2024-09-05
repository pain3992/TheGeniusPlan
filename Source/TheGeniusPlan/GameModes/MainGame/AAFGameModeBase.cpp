// Fill out your copyright notice in the Description page of Project Settings.

#include "AAFGameModeBase.h"
#include "AAFGameState.h"
#include "TheGeniusPlan/Player/GeniusPlayerController.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "TheGeniusPlan/TheGeniusPlanCharacter.h"
#include "TheGeniusPlan/GameModes/GeniusGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "TheGeniusPlan/HUD/AAFHUD.h"
#include "TheGeniusPlan/Actor/AAFLandLoction.h"
#include "Net/UnrealNetwork.h"

void AAAFGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAAFGameModeBase::BeginPlay()
{
	UGeniusGameInstance* GameInstance = Cast<UGeniusGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		GameInstance->Number = 8;
	}
}

void AAAFGameModeBase::TravelLevel()
{
	//FString TravelURL = FString::Printf(TEXT("/Game/Levels/MainLevel?game=/Script/TheGeniusPlan.AAFGameModeBase"));
	//GetWorld()->ServerTravel(TravelURL);
}

AAAFGameModeBase::AAAFGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C'"));
	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PlayerControllerClass = AGeniusPlayerController::StaticClass();
	GameStateClass = AAAFGameState::StaticClass();
	PlayerStateClass = AAAFPlayerState::StaticClass();
	HUDClass = AAAFHUD::StaticClass();
}

void AAAFGameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

