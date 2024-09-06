// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFPlayerController.h"



#include "TheGeniusPlan/Player/GeniusPlayerController.h"
#include "TheGeniusPlan/Widget/MainGame/AAFSelectWidget.h"
#include "TheGeniusPlan/Widget/MainGame/ShowPlayerSeletedLandWidget.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "TheGeniusPlan/GameModes/MainGameStateBase.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "TheGeniusPlan/GameModes/MainGame/AAFGameState.h"
#include "TheGeniusPlan/Widget/TimerWidget.h"
#include "TheGeniusPlan/Widget/MainGame/MainGameWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TheGeniusPlan/Actor/AAFLandLoction.h"


AAAFPlayerController::AAAFPlayerController()
{

}

void AAAFPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GameState = Cast<AAAFGameState>(GetWorld()->GetGameState());
	BindDispatcher();
}

void AAAFPlayerController::GameStepChange(EGameStep NewStep)
{
	UE_LOG(LogTemp, Error, TEXT("New Step : %d"), NewStep);

	if (GameState)
	{
		switch (NewStep)
		{
		case EGameStep::SetLocation:
			RequestGameStateFunction();
			break;
		case EGameStep::RoundStart:
			MoveActor();
			break;
		default:
			break;
		}
	}


}

void AAAFPlayerController::BindDispatcher()
{
	if (PlayerState != nullptr)
	{
		CastPlayerState = Cast<AAAFPlayerState>(PlayerState);

		if (GameState)
		{
			if (!GameState->EventDisptacherGameStepChange.IsBound())
			{
				GameState->EventDisptacherGameStepChange.AddDynamic(this, &AAAFPlayerController::GameStepChange);
				UE_LOG(LogTemp, Error, TEXT("Bind Success"));
			}

			GetWorld()->GetTimerManager().ClearTimer(TimerHandletwo);
			return;
		}
	}

	FTimerManager& timerManger = GetWorld()->GetTimerManager();
	timerManger.SetTimer(TimerHandletwo, this, &AAAFPlayerController::BindDispatcher, 0.1f, false);
}

void AAAFPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AAAFPlayerController::MoveActor()
{
	Server_MoveActor();
}

void AAAFPlayerController::RequestGameStateFunction()
{
	ResponseGameStateFunction();
}

void AAAFPlayerController::ResponseGameStateFunction_Implementation()
{
	GameState->RequestGameStepReset();
}

void AAAFPlayerController::Client_MoveActor_Implementation()
{
	APawn* thisPawn = GetPawn();

	if (thisPawn)
	{
		if (CastPlayerState)
		{
			FVector NewLocation = CastPlayerState->Location;
			thisPawn->SetActorLocation(NewLocation);
			UE_LOG(LogTemp, Error, TEXT("ActorMove : %f, %f, %f"), NewLocation.X, NewLocation.Y, NewLocation.Z);
		}
	}

}

void AAAFPlayerController::Server_MoveActor_Implementation()
{
	Client_MoveActor();
}


