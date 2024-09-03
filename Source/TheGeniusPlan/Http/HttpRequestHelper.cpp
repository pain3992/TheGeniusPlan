#include "HttpRequestHelper.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"


void UHttpRequstHelper::SendHttpRequest(const FString& Url, const TSharedPtr<FJsonObject> JsonObject, const FString& Verb, FHttpResponseDelegate ResponseDelegate)
{
	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

    Request->SetURL(Url);
    Request->SetVerb(Verb);
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	if (JsonObject.IsValid() &&  (Verb != TEXT("GET")))
	{
	   FString ContentString;
	   TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
	   FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	   Request->SetContentAsString(ContentString);
	}

	// 외부에서 전달된 콜백을 바인딩
	Request->OnProcessRequestComplete().BindLambda([ResponseDelegate](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
	   // 콜백 호출
	   ResponseDelegate.ExecuteIfBound(Request, Response, bWasSuccessful);
	});

	Request->ProcessRequest();
}

void UHttpRequstHelper::SendGetRequest(const FString& Url, FHttpResponseDelegate ResponseDelegate)
{
	SendHttpRequest(Url, nullptr, TEXT("GET"), ResponseDelegate);
}

void UHttpRequstHelper::SendPostRequest(const FString& Url, const TSharedPtr<FJsonObject> JsonObject, FHttpResponseDelegate ResponseDelegate)
{
	SendHttpRequest(Url, JsonObject, TEXT("POST"), ResponseDelegate);
}

void UHttpRequstHelper::SendPatchRequest(const FString& Url, const TSharedPtr<FJsonObject> JsonObject, FHttpResponseDelegate ResponseDelegate)
{
	SendHttpRequest(Url, JsonObject, TEXT("PATCH"), ResponseDelegate);
}

void UHttpRequstHelper::SendDeleteRequest(const FString& Url, FHttpResponseDelegate ResponseDelegate)
{
	SendHttpRequest(Url, nullptr, TEXT("DELETE"), ResponseDelegate);
}