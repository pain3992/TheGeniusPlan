// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFGameModeBase.h"
#include "AAFGameState.h"
#include "TheGeniusPlan/Player/GeniusPlayerController.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "TheGeniusPlan/TheGeniusPlanCharacter.h"

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

	if(CastGameState)
	{
		UE_LOG(LogTemp, Error, TEXT("GameState Cast Success"));
	}
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
