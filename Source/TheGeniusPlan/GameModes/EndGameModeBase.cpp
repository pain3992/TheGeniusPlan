// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameModeBase.h"
#include "GeniusGameInstance.h"
#include "GameFramework/GameState.h"
#include "TheGeniusPlan/Player/EndPlayerState.h"

AEndGameModeBase::AEndGameModeBase()
{
	PlayerStateClass = AEndPlayerState::StaticClass();
}

void AEndGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGeniusGameInstance* GameInstance = Cast<UGeniusGameInstance>(GetGameInstance());
	UE_LOG(LogTemp, Error, TEXT("Number is %d"), GameInstance->Number);

	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AEndGameModeBase::PlayerSendNumber, 5.0f, false);

}

void AEndGameModeBase::PlayerSendNumber()
{
	UE_LOG(LogTemp, Error, TEXT("PlayerState Number Change start"));

	TArray<APlayerState*> PlayerStateArray = GameState->PlayerArray;

	for(auto PlayerState : PlayerStateArray)
	{
		AEndPlayerState* CastState = Cast<AEndPlayerState>(PlayerState);
		UGeniusGameInstance* GameInstance = Cast<UGeniusGameInstance>(GetGameInstance());
		UE_LOG(LogTemp, Error, TEXT("%d"), GameInstance->Number);
		CastState->PlayerStateNumberSet(GameInstance->Number);
	}

	UE_LOG(LogTemp, Error, TEXT("PlayerState Number Change End"));
}
