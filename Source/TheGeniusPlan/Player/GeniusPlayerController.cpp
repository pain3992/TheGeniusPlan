// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Player/GeniusPlayerController.h"
#include "TheGeniusPlan/Widget/MainGame/AAFSelectWidget.h"
#include "TheGeniusPlan/Widget/MainGame/ShowPlayerSeletedLandWidget.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameStateBase.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "TheGeniusPlan/GameModes/MainGame/AAFGameState.h"
#include "TheGeniusPlan/ChatComponent.h"
#include "TheGeniusPlan/Widget/TimerWidget.h"
#include "TheGeniusPlan/Widget/MainGame/MainGameWidget.h"


AGeniusPlayerController::AGeniusPlayerController()
{

	static ConstructorHelpers::FClassFinder<UShowPlayerSeletedLandWidget> CShowLandWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/MainGame/Widget/WG_ShowSelectedLand.WG_ShowSelectedLand_C'"));
	static ConstructorHelpers::FClassFinder<UAAFSelectWidget> CSelectWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/MainGame/Widget/WG_SelectedWidget.WG_SelectedWidget_C'"));
	static ConstructorHelpers::FClassFinder<UTimerWidget> CTimerWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/MainGame/Widget/WG_Timer.WG_Timer_C'"));

	if (CShowLandWidget.Succeeded())
	{
		SelectResultWidgetClass = CShowLandWidget.Class;
	}
	if (CSelectWidget.Succeeded())
	{
		SelectLandWidgetClass = CSelectWidget.Class;
	}
	if (CTimerWidget.Succeeded())
	{
		TimerWidgetClass = CTimerWidget.Class;
	}

	ChatComponent = CreateDefaultSubobject<UChatComponent>(TEXT("ChatComponent"));

	if (ChatComponent)
	{

	}

	TimerWidget = nullptr;
	IsCreateWidget = false;
}

void AGeniusPlayerController::CreateVoteWidget()
{

	if (SelectLandWidget == nullptr)
	{
		SelectLandWidget = Cast<UAAFSelectWidget>(CreateWidget(GetWorld(), SelectLandWidgetClass));
		SelectLandWidget->AddToViewport();
	}
	else
	{
		if (SelectLandWidget->IsInViewport())
		{

		}
		else
		{
			SelectLandWidget->AddToViewport();
		}
	}

	bShowMouseCursor = true;

}

void AGeniusPlayerController::BeginPlay()
{
	Super::BeginPlay();

	BindDispatcher();

	GameState = Cast<AAAFGameState>(GetWorld()->GetGameState());
	GameState->SetGameStep(EGameStep::Vote);

	//CreateTimerWidget();

}

void AGeniusPlayerController::CreateResultWidget(uint8 firstNumber, uint8 SecondsNumber)
{
	if (SelectResultWidgetClass)
	{
		if (SelectResultWidget == nullptr)
		{
			SelectResultWidget = Cast<UShowPlayerSeletedLandWidget>(CreateWidget(GetWorld(), SelectResultWidgetClass));
			SelectResultWidget->SetTextBox(firstNumber, SecondsNumber);
			SelectResultWidget->AddToViewport();
		}
		else
		{
			if (!SelectResultWidget->IsInViewport())
			{
				SelectResultWidget->SetTextBox(firstNumber, SecondsNumber);
				SelectResultWidget->AddToViewport();
			}
			else
			{
				SelectResultWidget->SetTextBox(firstNumber, SecondsNumber);
			}
		}
	}
}

void AGeniusPlayerController::GameStepChange(EGameStep NewStep)
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (GameState)
	{
		switch (NewStep)
		{
		case EGameStep::None:
			break;
		case EGameStep::Vote:
			CreateVoteWidget();
			break;
		case EGameStep::Result:
			SelectLandWidget->RemoveFromParent();
			CreateResultWidget(GameState->AbundanceLand, GameState->FamineLand);
			break;
		case EGameStep::MoveActor:
			SelectResultWidget->RemoveFromParent();
			{
				AAAFPlayerState* CastPlayerState = Cast<AAAFPlayerState>(PlayerState);

				if (CastPlayerState)
				{
					switch (CastPlayerState->SelectedLand)
					{
					case ESelectedLand::FamineLand:
						break;
					case ESelectedLand::AbundanceLand:
						break;

					case ESelectedLand::None:
						break;

					default:
						break;
					}
				}
			}
			break;

		case EGameStep::GameEnd:
			GetPawn()->SetActorLocation(FVector(0, 0, 0));
			break;
		default:
			break;
		}
	}


}

void AGeniusPlayerController::RemoveResultWidget()
{
	SelectResultWidget->RemoveFromParent();
}

void AGeniusPlayerController::BindDispatcher()
{

	if (GameState)
	{
		if (!GameState->EventDisptacherGameStepChange.IsBound())
		{
			GameState->EventDisptacherGameStepChange.AddDynamic(this, &AGeniusPlayerController::GameStepChange);
			AGeniusPlayerController::GameStepChange(GameState->GetGameStep());
			return;
		}
	}

	FTimerManager& timerManger = GetWorld()->GetTimerManager();
	timerManger.SetTimer(TimerHandletwo, this, &AGeniusPlayerController::BindDispatcher, 0.1f, false);
}

void AGeniusPlayerController::CheckPlayerAllSelected()
{
	TArray<APlayerState*> PlayerStates = GetWorld()->GetGameState()->PlayerArray;

	if (PlayerStates.Num() > 0)
	{
		for (auto ClientPlayerState : PlayerStates)
		{
			AAAFPlayerState* ClientState = Cast<AAAFPlayerState>(ClientPlayerState);

			if (ClientState)
			{
				switch (ClientState->GetSelectedLand())
				{
				case ESelectedLand::None:
					AbundanceLand = 0;
					FamineLand = 0;
					return;
					break;
				case ESelectedLand::AbundanceLand:
					AbundanceLand++;
					break;
				case ESelectedLand::FamineLand:
					FamineLand++;
					break;
				default:
					break;
				}
			}
		}

		UE_LOG(LogTemp, Error, TEXT("All Selected!"));
		RequestChangetStepOnServer(EGameStep::Result, AbundanceLand, FamineLand);
	}
}

void AGeniusPlayerController::CreateTimerWidget_Implementation()
{

	//if (TimerWidgetClass)
	//{
	//	if (TimerWidget == nullptr)
	//	{
	//		TimerWidget = CreateWidget<UTimerWidget>(GetWorld(), TimerWidgetClass);
	//		IsCreateWidget = true;

	//		if (TimerWidget)
	//		{
	//			TimerWidget->AddToViewport();
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemp, Error, TEXT("Widget Create Fail"));
	//		}
	//	}
	//	else
	//	{

	//		UE_LOG(LogTemp, Error, TEXT("TimerWidget Not Null"));

	//		if (TimerWidget->IsInViewport())
	//		{

	//		}
	//		else
	//		{
	//			TimerWidget->AddToViewport();
	//		}
	//	}
	//}

}

void AGeniusPlayerController::UpdateTimerWidget(double NewTime)
{
	AMainGameHUD* GameHUD = Cast<AMainGameHUD>(GetHUD());

	if (GameHUD)
	{
		if(GameHUD->MainGameWidget)
		{
			GameHUD->MainGameWidget->UpdateCountdownDisplay(60);
		}
		
	}

	//if(TimerWidget != nullptr && TimerWidget->IsInViewport())
	//{
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("TimerWidget is either null or not in viewport."));
	//}
}

void AGeniusPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//if (IsCreateWidget)
	//{
	//	if (GameState)
	//	{
	//		if (TimerWidget)
	//		{
	//			UpdateTimerWidget(GameState->Timer);
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemp, Error, TEXT("TimerWidget is null."));
	//		}
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Error, TEXT("GameState is null."));
	//	}
	//}
}

void AGeniusPlayerController::RequestServerChangeStep()
{
	GameState->SetGameStep(EGameStep::MoveActor);
}

void AGeniusPlayerController::MoveActor()
{
	AAAFPlayerState* CastPlayerState = Cast<AAAFPlayerState>(PlayerState);

	UE_LOG(LogTemp, Error, TEXT("MoveActor Function Play"));
	
	switch (CastPlayerState->SelectedLand)
	{
	case ESelectedLand::AbundanceLand:
		break;
	case ESelectedLand::FamineLand:
		break;
	case ESelectedLand::None:
		break;
	default:
		break;
	}

}

void AGeniusPlayerController::RequestChangetStepOnServer_Implementation(EGameStep NewStep, uint8 FirstLand, uint8 SecondsLand)
{
	if (GameState)
	{
		GameState->SetGameStep(NewStep);
		GameState->SetLandCount(FirstLand, SecondsLand);
		
		GetWorld()->GetTimerManager().SetTimer(TimerHandlePC, this, &AGeniusPlayerController::RequestServerChangeStep, 10.0f, false);
	}

}
