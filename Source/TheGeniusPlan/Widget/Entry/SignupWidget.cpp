// Fill out your copyright notice in the Description page of Project Settings.


#include "SignupWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "TheGeniusPlan/Http/HttpRequestHelper.h"

void USignupWidget::NativeConstruct()
{
	if(ButtonCansel)
	{
		ButtonCansel->OnClicked.AddDynamic(this, &USignupWidget::ClickedButtonCansel);
	}

	if(ButtonSignup)
	{
		ButtonSignup->OnClicked.AddDynamic(this, &USignupWidget::ClickedButtonSignup);
	}
}

void USignupWidget::ClickedButtonSignup()
{
	if (EntryHUD && EditableUsername && EditableLoginID && EditablePassword && EditablePasswordCheck)
	{
		
		FString Url = TEXT("http://localhost:3000/user/signup");
		
		// JSON 객체 생성
		
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		
		JsonObject->SetStringField(TEXT("login_id"), EditableLoginID->GetText().ToString());
		JsonObject->SetStringField(TEXT("username"), EditableUsername->GetText().ToString());
		JsonObject->SetStringField(TEXT("password"), EditablePassword->GetText().ToString());
		JsonObject->SetStringField(TEXT("password_check"), EditablePasswordCheck->GetText().ToString());

		// HTTP 요청 보내기 (POST 요청 예시)
		UHttpRequstHelper::SendPostRequest(
			Url,
			JsonObject,
			FHttpResponseDelegate::CreateUObject(this, &USignupWidget::OnHttpResponse));
		UE_LOG(LogTemp, Warning, TEXT("HUD is Vaild"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD is Null"));
	}
	// SetVisibility(ESlateVisibility::Collapsed);
}

void USignupWidget::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		TSharedPtr<FJsonObject> JsonResponse;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonResponse) && JsonResponse.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Request Success"));
			UE_LOG(LogTemp, Warning, TEXT("Response : %s"), *Response->GetContentAsString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Request Fail"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Request Fail"));
	}
}

void USignupWidget::ClickedButtonCansel()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

