// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/widget/Entry/SignupWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "TheGeniusPlan/Http/HttpRequestHelper.h"

void USignupWidget::NativeConstruct()
{
	if(ButtonCancel)
	{
		ButtonCancel->OnClicked.AddDynamic(this, &USignupWidget::ClickedButtonCansel);
	}

	if(ButtonSignup)
	{
		ButtonSignup->OnClicked.AddDynamic(this, &USignupWidget::ClickedButtonSignup);
	}
}

void USignupWidget::ClickedButtonSignup()
{
	if (EntryHUD && EditableTextID && EditableTextUsername && EditableTextUsername && EditableTextPassword && EditableTextPasswordCheck)
	{
		FString Url = TEXT("http://127.0.0.1:3000/user/signup");
		
		// JSON 객체 생성
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

		JsonObject->SetStringField(TEXT("login_id"), EditableTextID->GetText().ToString());
		JsonObject->SetStringField(TEXT("username"), EditableTextUsername->GetText().ToString());
		JsonObject->SetStringField(TEXT("password"), EditableTextPassword->GetText().ToString());
		JsonObject->SetStringField(TEXT("password_check"), EditableTextPasswordCheck->GetText().ToString());
	
		// HTTP 요청 보내기 (POST 요청 예시)
		UHttpRequstHelper::SendPostRequest(
			Url,
			JsonObject,
			FHttpResponseDelegate::CreateUObject(this, &USignupWidget::OnHttpResponse));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD is Null"));
	}
	// SetVisibility(ESlateVisibility::Collapsed);
}

void USignupWidget::OnHttpResponse(bool bWasSuccessful, TSharedPtr<FJsonObject> JsonResponse,
	const FString& ErrorMessage)
{
	if (bWasSuccessful)
	{
		TSharedPtr<FJsonObject> JsonData = JsonResponse->GetObjectField(TEXT("data"));

		FStringView ParseLoginID(TEXT("login_id"));
		FStringView ParseUserName(TEXT("username"));
		
		int32 ID = JsonData->GetIntegerField(TEXT("id"));
		FString LoginID = JsonData->GetStringField(ParseLoginID);
		FString UserName = JsonData->GetStringField(ParseUserName);
		// 회원가입 후 바로 로그인 처리

		UE_LOG(LogTemp, Log, TEXT("Received Value: %s, Number: %s"), *LoginID, *UserName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Signup: %s"), *ErrorMessage);
	}
}


void USignupWidget::ClickedButtonCansel()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

