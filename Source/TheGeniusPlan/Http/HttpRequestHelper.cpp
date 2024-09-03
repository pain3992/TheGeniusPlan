#include "HttpRequestHelper.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

void UHttpRequstHelper::HandleResponse(FHttpResponsePtr Response, bool bWasSuccessful, FHttpResponseDelegate ResponseDelegate)
{
	if (bWasSuccessful && Response.IsValid())
	{
		TSharedPtr<FJsonObject> JsonResponse;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonResponse) && JsonResponse.IsValid())
		{
			// 실패 여부 확인: statusCode또는 message 필드가 있는 경우
			// if (JsonResponse->HasField(TEXT("statusCode")) || JsonResponse->HasField(TEXT("message")))
			if (JsonResponse->HasField(TEXT("data")))
			{
				// 성공적인 응답으로 간주하고 콜백 호출
				ResponseDelegate.ExecuteIfBound(true, JsonResponse, TEXT(""));
			}
			else
			{
				// 실패한 응답으로 간주하고 콜백 호출
				FString ErrorMessage = JsonResponse->GetStringField(TEXT("message"));
				ResponseDelegate.ExecuteIfBound(false, nullptr, ErrorMessage);
			}
		}
		else
		{
			ResponseDelegate.ExecuteIfBound(false, nullptr, TEXT("Failed to parse JSON response"));
		}
	}
	else
	{
		ResponseDelegate.ExecuteIfBound(false, nullptr, TEXT("HTTP Request failed"));
	}
}

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
	   HandleResponse(Response, bWasSuccessful, ResponseDelegate);
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