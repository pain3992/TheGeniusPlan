// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/GameModes/MainGame/MainGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AMainGameModeBase::AMainGameModeBase()
{
	TotalRounds = 0;
	CurrentRound = 0;

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AMainGameModeBase::HandleGameStart()
{
	SelectNextGameMode();
}

void AMainGameModeBase::SelectNextGameMode()
{
	if (PossibleGameModes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, PossibleGameModes.Num() - 1);
		TSubclassOf<AGameMode> SelectedGameMode = PossibleGameModes[RandomIndex];

		FString Options = FString::Printf(TEXT("?game=%s"), *SelectedGameMode->GetName());
		UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), true, Options);
	}
}

// void AMainGameModeBase::TransitionToNextRound()
// {
// }
//
// void AMainGameModeBase::HandleRoundEnd()
// {
// }
//
// void AMainGameModeBase::CheckForOverallWinner()
// {
// }
//
//
// void AMainGameModeBase::EndMatch(int32 WinningPlayerId)
// {
// }
