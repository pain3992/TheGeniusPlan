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
	if (EntryHUD && EditableTextID && EditableTextPassword)
	{
		FString Url = TEXT("http://localhost:3000/user/login");
		// JSON 객체 생성
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		JsonObject->SetStringField(TEXT("login_id"), EditableTextID->GetText().ToString());
		JsonObject->SetStringField(TEXT("password"), EditableTextPassword->GetText().ToString());

		// HTTP 요청 보내기 (POST 요청 예시)
		UHttpRequstHelper::SendPostRequest(
			Url,
			JsonObject,
			FHttpResponseDelegate::CreateUObject(this, &ULoginWidget::OnHttpResponse));
		UE_LOG(LogTemp, Warning, TEXT("HUD is Vaild"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD is Null"));
	}
}

void ULoginWidget::Reset() const
{
	if (EditableTextID)
	{
		EditableTextID->SetText(FText::FromString(TEXT("")));
	}
	if (EditableTextPassword)
	{
		EditableTextPassword->SetText(FText::FromString(TEXT("")));
	}
}

void ULoginWidget::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		TSharedPtr<FJsonObject> JsonResponse;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonResponse) && JsonResponse.IsValid())
		{
			if (JsonResponse->HasField(TEXT("data")))
			{
				TSharedPtr<FJsonObject> JsonData = JsonResponse->GetObjectField(TEXT("data"));
				FStringView ParseLoginID(TEXT("login_id"));
				FStringView ParseUserName(TEXT("username"));

				FString LoginID = JsonData->GetStringField(ParseLoginID);
				FString UserName = JsonData->GetStringField(ParseUserName);
				UE_LOG(LogTemp, Log, TEXT("Received Value: %s, Number: %s"), *LoginID, *UserName);

				EntryHUD->ShowWidget(EntryWidgetType::EntryWidget);
			}
			else
			{
				FStringView ParseErrorMessage(TEXT("message"));
				FString ErrorMessage = JsonResponse->GetStringField(ParseErrorMessage);
				UE_LOG(LogTemp, Log, TEXT("ErrorMessage: %s"), *ErrorMessage);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON response"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HTTP Request failed"));
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
