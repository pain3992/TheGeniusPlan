// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/Widget/Entry/LoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"
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
		FString Url = TEXT("http://127.0.0.1:3000/user/login");
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
		FString LoginID = JsonData->GetStringField(ParseLoginID);
		FString UserName = JsonData->GetStringField(ParseUserName);

		UE_LOG(LogTemp, Log, TEXT("Received Value: %s, Number: %s"), *LoginID, *UserName);
		EntryHUD->ShowWidget(EntryWidgetType::LobbyWidget);
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
