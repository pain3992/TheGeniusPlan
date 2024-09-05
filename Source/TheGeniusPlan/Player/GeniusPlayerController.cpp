// Fill out your copyright notice in the Description page of Project Settings.


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


AGeniusPlayerController::AGeniusPlayerController()
{

}

void AGeniusPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GameState = Cast<AAAFGameState>(GetWorld()->GetGameState());
	BindDispatcher();
	UE_LOG(LogTemp, Error, TEXT("PlayerController Step : %d"), GameState->GetGameStep());
}

void AGeniusPlayerController::GameStepChange(EGameStep NewStep)
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

void AGeniusPlayerController::BindDispatcher()
{
	if (PlayerState != nullptr)
	{
		CastPlayerState = Cast<AAAFPlayerState>(PlayerState);

		if (GameState)
		{
			if (!GameState->EventDisptacherGameStepChange.IsBound())
			{
				GameState->EventDisptacherGameStepChange.AddDynamic(this, &AGeniusPlayerController::GameStepChange);
				UE_LOG(LogTemp, Error, TEXT("Bind Success"));
			}

			GetWorld()->GetTimerManager().ClearTimer(TimerHandletwo);
			return;
		}
	}

	FTimerManager& timerManger = GetWorld()->GetTimerManager();
	timerManger.SetTimer(TimerHandletwo, this, &AGeniusPlayerController::BindDispatcher, 0.1f, false);
}

void AGeniusPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}
//
//void AGeniusPlayerController::RequestServerChangeStep()
//{
//	
//}

void AGeniusPlayerController::MoveActor()
{
	Server_MoveActor();
}

void AGeniusPlayerController::RequestGameStateFunction()
{
	ResponseGameStateFunction();
}

void AGeniusPlayerController::ResponseGameStateFunction_Implementation()
{
	GameState->RequestGameStepReset();
}

void AGeniusPlayerController::Client_MoveActor_Implementation()
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

void AGeniusPlayerController::Server_MoveActor_Implementation()
{
	Client_MoveActor();
}

//void AGeniusPlayerController::Req_GameStepChange()
//{
//	Server_GameStepChange();
//}
//
//void AGeniusPlayerController::Server_GameStepChange_Implementation()
//{
//	if (GameState)
//	{
//		GameState->SetGameStep(EGameStep::RoundStart);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("GameState Is Null"));
//	}
//}
