// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFGameModeBase.h"
#include "AAFGameState.h"
#include "TheGeniusPlan/Player/GeniusPlayerController.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "TheGeniusPlan/TheGeniusPlanCharacter.h"
#include "TheGeniusPlan/GameModes/GeniusGameInstance.h"

void AAAFGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//if (CastGameState)
	//{
	//	CastGameState->Timer += DeltaSeconds;
	//}
	//else                                                                                                          
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Timer Update By GameMode"));
	//}
}

void AAAFGameModeBase::BeginPlay()
{
	CastGameState = Cast<AAAFGameState>(GameState);

	if (CastGameState)
	{
		UE_LOG(LogTemp, Error, TEXT("AAAFGameMode Base Start"));
	}

	UGeniusGameInstance* GameInstance = Cast<UGeniusGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		GameInstance->Number = 8;
	}

	GetWorld()->GetTimerManager().SetTimer(GameModeSecondHandle, this, &AAAFGameModeBase::ChangeEndGame, 10.0f, false);
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
}

void AAAFGameModeBase::BindGameState()
{
	if (CastGameState)
	{
		if (!CastGameState->EventDisptacherGameStepChange.IsBound())
		{
			CastGameState->EventDisptacherGameStepChange.AddDynamic(this, &AAAFGameModeBase::GameStepChange);
			return;
		}
	}

	FTimerManager& timerManger = GetWorld()->GetTimerManager();
	timerManger.SetTimer(GameModeTimerHandle, this, &AAAFGameModeBase::BindGameState, 0.1f, false);
}

void AAAFGameModeBase::GameStepChange(EGameStep NewStep)
{
	if (NewStep == EGameStep::GameEnd)
	{

	}

}

void AAAFGameModeBase::ChangeEndGame()
{
	FString TravelURL = FString::Printf(TEXT("/Game/Levels/EndLevel?game=/Script/TheGeniusPlan.MainGameModeBase"));
	GetWorld()->ServerTravel(TravelURL);
}
