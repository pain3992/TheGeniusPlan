// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Player/GeniusPlayerController.h"
#include "TheGeniusPlan/Widget/MainGame/AAFSelectWidget.h"
#include "TheGeniusPlan/Widget/MainGame/ShowPlayerSeletedLandWidget.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameStateBase.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "TheGeniusPlan/GameModes/MainGame/AAFGameState.h"
#include "TheGeniusPlan/ChatComponent.h"

AGeniusPlayerController::AGeniusPlayerController()
{
	static ConstructorHelpers::FClassFinder<UShowPlayerSeletedLandWidget> CShowLandWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/MainGame/Widget/WG_ShowSelectedLand.WG_ShowSelectedLand_C'"));
	static ConstructorHelpers::FClassFinder<UAAFSelectWidget> CSelectWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/MainGame/Widget/WG_SelectedWidget.WG_SelectedWidget_C'"));

	if (CShowLandWidget.Succeeded())
	{
		SelectResultWidgetClass = CShowLandWidget.Class;
	}
	if (CSelectWidget.Succeeded())
	{
		SelectLandWidgetClass = CSelectWidget.Class;
	}

	Timer = 0.0f;
	DeltaTimer = 60.0f;
	ActiveTimer = 0;

	ChatComponent = CreateDefaultSubobject<UChatComponent>(TEXT("ChatComponent"));

	if (ChatComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ChatComponent Create Succeeded!"));
	}
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

	//AAAFGameState* GameState = Cast<AAAFGameState>(GetWorld()->GetGameState());
	//GameState->SetGameStep(EGameStep::Vote);
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

	UE_LOG(LogTemp, Error, TEXT("Client Game Step Change"));
	AAAFGameState* GameState = Cast<AAAFGameState>(GetWorld()->GetGameState());
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (GameState)
	{
		switch (NewStep)
		{
		case EGameStep::None:
			UE_LOG(LogTemp, Error, TEXT("Game Step Is None Step"));
			break;
		case EGameStep::Vote:
			CreateVoteWidget();
			ActiveTimer = 1;
			SelectLandWidget->SetTimer(DeltaTimer);
			TimerManager.SetTimer(TimerHandle, this, &AGeniusPlayerController::SetTimerWidget, 0.5f, true);
			UE_LOG(LogTemp, Error, TEXT("Game Step Is Vote Step"));
			break;
		case EGameStep::Result:
			CreateResultWidget(GameState->AbundanceLand, GameState->FamineLand);
			ActiveTimer = 2;
			SelectResultWidget->SetTimer(DeltaTimer);
			TimerManager.SetTimer(TimerHandle, this, &AGeniusPlayerController::SetTimerWidget, 0.5f, true);
			UE_LOG(LogTemp, Error, TEXT("Game Step Is Result Step"));
			break;
		case EGameStep::GameEnd:
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

void AGeniusPlayerController::SetTimerWidget()
{
	ServerRequestCurrentTime();

	if (Timer >= 1.0f && DeltaTimer >= 0.0f)
	{
		DeltaTimer -= Timer;

		if (ActiveTimer == 1)
		{
			SelectLandWidget->SetTimer(DeltaTimer);
		}
		else if (ActiveTimer == 2)
		{
			SelectResultWidget->SetTimer(DeltaTimer);
		}
		else
		{

		}
	}
	
	if(DeltaTimer <= 0.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		DeltaTimer = 60.0f;
	}

}

void AGeniusPlayerController::ServerRequestCurrentTime_Implementation()
{
	float ServerTimer = GetWorld()->GetDeltaSeconds();
	ClientReciveCurrentTime(ServerTimer);
}

void AGeniusPlayerController::ClientReciveCurrentTime_Implementation(float Time)
{
	Timer += Time;
}

void AGeniusPlayerController::BindDispatcher()
{
	AAAFGameState* GameStateBase = Cast<AAAFGameState>(GetWorld()->GetGameState());

	if (GameStateBase)
	{
		if (!GameStateBase->EventDisptacherGameStepChange.IsBound())
		{
			GameStateBase->EventDisptacherGameStepChange.AddDynamic(this, &AGeniusPlayerController::GameStepChange);
			AGeniusPlayerController::GameStepChange(GameStateBase->GetGameStep());
			UE_LOG(LogTemp, Error, TEXT("GameStep dispatcher Bind"));
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

		RequestChangetStepOnServer(EGameStep::Result, AbundanceLand, FamineLand);
	}
}

void AGeniusPlayerController::RequestChangetStepOnServer_Implementation(EGameStep NewStep, uint8 FirstLand, uint8 SecondsLand)
{
	AAAFGameState* GameState = Cast<AAAFGameState>(GetWorld()->GetGameState());

	if (GameState)
	{
		GameState->SetGameStep(NewStep);
		GameState->SetLandCount(FirstLand, SecondsLand);
	}

}
