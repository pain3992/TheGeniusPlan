// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/Widget/Entry/LoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TheGeniusPlan/GameModes/GeniusGameInstance.h"
#include "TheGeniusPlan/Http/HttpRequestHelper.h"
#include "TheGeniusPlan/HUD/EntryHUD.h"

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonLogin)
	{
		ButtonLogin->OnClicked.AddDynamic(this, &ULoginWidget::ClickedLogin);
	}
	if (ButtonQuit)
	{
		ButtonQuit->OnClicked.AddDynamic(this, &ULoginWidget::ClickedQuit);
	}
	if (ButtonSignUp)
	{
		ButtonSignUp->OnClicked.AddDynamic(this, &ULoginWidget::ClickedSignUp);
	}
}

void ULoginWidget::ClickedLogin()
{
	if (EntryHUD && EditableTextLoginID && EditableTextLoginPassword)
	{
		// 로컬 API에 연결시 (테스트용)
		// FString Url = TEXT("http://127.0.0.1:3000/user/login");
		// API 서버에 연결시 (배포용)
		FString Url = TEXT("http://34.41.211.121:3000/user/login");
		// JSON 객체 생성
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		JsonObject->SetStringField(TEXT("login_id"), EditableTextLoginID->GetText().ToString());
		JsonObject->SetStringField(TEXT("password"), EditableTextLoginPassword->GetText().ToString());

		// HTTP 요청 보내기 (POST 요청 예시)
		// UHttpRequstHelper::SendPostRequest(Url, JsonObject, FHttpResponseDelegate::CreateUObject(this, &ULoginWidget::OnHttpResponse));
		UHttpRequstHelper::SendPostRequest(Url, JsonObject, FHttpResponseDelegate::CreateUObject(this, &ULoginWidget::OnHttpResponse));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD is Null"));
	}
}

void ULoginWidget::Reset() const
{
	if (EditableTextLoginID)
	{
		EditableTextLoginID->SetText(FText::FromString(TEXT("")));
	}
	if (EditableTextLoginPassword)
	{
		EditableTextLoginPassword->SetText(FText::FromString(TEXT("")));
	}
}

void ULoginWidget::OnHttpResponse(bool bWasSuccessful, TSharedPtr<FJsonObject> JsonResponse, const FString& ErrorMessage)
{
	if (bWasSuccessful)
	{
		TSharedPtr<FJsonObject> JsonData = JsonResponse->GetObjectField(TEXT("data"));

		FStringView ParseLoginID(TEXT("login_id"));
		FStringView ParseUserName(TEXT("username"));

		// 회원가입한 유저 정보 및 랭킹 정보
		int32 ID = JsonData->GetIntegerField(TEXT("id"));
		FString LoginID = JsonData->GetStringField(ParseLoginID);
		FString UserName = JsonData->GetStringField(ParseUserName);
		int32 Rank = JsonData->GetIntegerField(TEXT("rank"));
		int16 RankPoint = JsonData->GetIntegerField(TEXT("rank_point"));
		int32 RankPlayers = JsonData->GetIntegerField(TEXT("rank_players"));
		int16 TotalGame = JsonData->GetIntegerField(TEXT("total_game"));
		int16 TotalWin = JsonData->GetIntegerField(TEXT("total_win"));
		float WinRate = JsonData->GetIntegerField(TEXT("win_rate"));

		// 로그인 정보 출력
		UE_LOG(LogTemp, Log, TEXT("Received Value: %d"), RankPlayers);

		// GeniusGameInstance의 LoginInfo에 로그인 정보 저장
		if (UGeniusGameInstance* GameInstance = Cast<UGeniusGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		{
			// GameInstance->LoginInfo.ID = ID;
			FLoginInfo LoginInfo;
			LoginInfo.bIsLoggedIn = true;
			LoginInfo.LoginID = LoginID;
			LoginInfo.UserName = UserName;
			LoginInfo.Rank = Rank;
			LoginInfo.RankPoint = RankPoint;
			LoginInfo.RankPlayers = RankPlayers;
			LoginInfo.TotalGame = TotalGame;
			LoginInfo.TotalWin = TotalWin;
			LoginInfo.WinRate = WinRate;

            // 게임인스턴스에 로그인정보 저장 및 델리게이트 호출
			GameInstance->SetLoginInfo(LoginInfo);
			SetVisibility(ESlateVisibility::Collapsed);
			EntryHUD->ShowWidget(EntryWidgetType::LobbyWidget);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GameInstance is Null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP Request failed: %s"), *ErrorMessage);
	}
}

void ULoginWidget::ClickedQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void ULoginWidget::ClickedSignUp()
{
	if (EntryHUD)
	{
		EntryHUD->ShowWidget(EntryWidgetType::SignupWidget);
	}
}
