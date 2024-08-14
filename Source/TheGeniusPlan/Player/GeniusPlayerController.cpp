// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Player/GeniusPlayerController.h"
#include "TheGeniusPlan/Widget/MainGame/AAFSelectWidget.h"
#include "TheGeniusPlan/Widget/MainGame/ShowPlayerSeletedLandWidget.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameStateBase.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"

AGeniusPlayerController::AGeniusPlayerController()
{
	static ConstructorHelpers::FClassFinder<UShowPlayerSeletedLandWidget> CShowLandWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/MainGame/Widget/WG_ShowSelectedLand.WG_ShowSelectedLand_C'"));
	static ConstructorHelpers::FClassFinder<UAAFSelectWidget> CSelectWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/MainGame/Widget/WG_SelectedWidget.WG_SelectedWidget_C'"));

	if (CShowLandWidget.Succeeded())
	{
		ShowLandWidgetClass = CShowLandWidget.Class;
	}
	if (CSelectWidget.Succeeded())
	{
		SelectLandWidgetClass = CSelectWidget.Class;
	}

	Timer = 10.0f;


}

void AGeniusPlayerController::CreateVoteWidget()
{
	SelectLandWidget = Cast<UAAFSelectWidget>(CreateWidget(GetWorld(), SelectLandWidgetClass));

	if (SelectLandWidget)
	{
		SelectLandWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SelectLandWidget Create Fail"));
	}

	bShowMouseCursor = true;

}

void AGeniusPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		CreateVoteWidget();
	}
	PlayerStateBind();
}

void AGeniusPlayerController::SetDrawResultWidget_Implementation(uint8 firstNumber, uint8 SecondsNumber)
{
	// Server -> All Client 전달
	// HUD::CreateResultWidget(firstNumber, SecondNumber)
	AMainGameHUD* ClientHUD = Cast<AMainGameHUD>(GetHUD());
	if (ClientHUD)
	{
		ClientHUD->CreateResultWidget(firstNumber, SecondsNumber);
	}
	//if (ShowLandWidgetClass)
	//{
	//	ShowLandWidget = Cast<UShowPlayerSeletedLandWidget>(CreateWidget(GetWorld(), ShowLandWidgetClass));

	//	if (ShowLandWidget)
	//	{
	//		ShowLandWidget->SetTextBox(firstNumber, SecondsNumber);
	//		ShowLandWidget->AddToViewport();
	//		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGeniusPlayerController::SetTimerWidget, 1.0f, false);
	//	}
	//}
}

void AGeniusPlayerController::RemoveResultWidget()
{
	ShowLandWidget->RemoveFromParent();
}

void AGeniusPlayerController::SetTimerWidget()
{

	if (Timer > 0.0f && ShowLandWidget)
	{
		Timer -= 1.0f;
		ShowLandWidget->SetTimer(Timer);

	}
	else
	{
		Timer = 10.0f;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		ShowLandWidget->RemoveFromParent();
		ShowLandWidget->SetTextBox(0, 0);
		SelectLandWidget->AddToViewport();
	}


}

void AGeniusPlayerController::PlayerStateBind()
{

	if (PlayerState != nullptr)
	{
		AAAFPlayerState* AAPlayerState = Cast<AAAFPlayerState>(PlayerState);

		if (AAPlayerState)
		{
			if (!AAPlayerState->AllPlayerSelected.IsBound())
			{
				AAPlayerState->AllPlayerSelected.AddDynamic(this, &AGeniusPlayerController::AllPlayerSelectedCheck);
				UE_LOG(LogTemp, Error, TEXT("Successfully bound AllPlayerSelected"));
				return;
			}
			else if (AAPlayerState->AllPlayerSelected.IsBound())
			{
				UE_LOG(LogTemp, Error, TEXT("Already Bound"));
				return;
			}

		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerState Cast fail!"));
		}
	}

	FTimerManager& timerManger = GetWorld()->GetTimerManager();
	timerManger.SetTimer(TimerHandletwo, this, &AGeniusPlayerController::PlayerStateBind, 0.01f, false);
}


void AGeniusPlayerController::AllPlayerSelectedCheck()
{
	UE_LOG(LogTemp, Error, TEXT("AllPlayer Select Check"));

	AGameStateBase* GameStateBase = GetWorld()->GetGameState();

	if (GameStateBase)
	{
		TArray<APlayerState*> PlayerStates = GameStateBase->PlayerArray;

		for (auto ClientPlayerState : PlayerStates)
		{
			AAAFPlayerState* ClientPlayer = Cast<AAAFPlayerState>(ClientPlayerState);

			if (ClientPlayer)
			{

				if (ClientPlayer->GetSelectedLand() == ESelectedLand::None)
				{
					AbundanceLand = 0;
					FamineLand = 0;
					return;
				}
				else if (ClientPlayer->GetSelectedLand() == ESelectedLand::AbundanceLand)
				{
					AbundanceLand++;
				}
				else
				{
					FamineLand++;
				}

			}
		}

		UE_LOG(LogTemp, Error, TEXT("All Player Selected!"));
		Req_PlayerCreateResultWidget(AbundanceLand, FamineLand);
	}
}

void AGeniusPlayerController::Req_PlayerCreateResultWidget_Implementation(uint8 FNumber, uint8 SNumber)
{
	SetDrawResultWidget(FNumber, SNumber);
	//AGameStateBase* GameStateBase = GetWorld()->GetGameState();

	//if (GameStateBase)
	//{
	//	TArray<APlayerState*> PlayerStates = GameStateBase->PlayerArray;

	//	for (auto ClientPlayerState : PlayerStates)
	//	{
	//		AGeniusPlayerController* ClientController = Cast<AGeniusPlayerController>(ClientPlayerState->GetPlayerController());

	//		if (ClientController)
	//		{
	//			ClientController->CreateResultWidget(FNumber, SNumber);
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemp, Error, TEXT("ClientController Cast fail"));
	//		}
	//	}
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("GameStateBase Cast Fail"));
	//}
}
