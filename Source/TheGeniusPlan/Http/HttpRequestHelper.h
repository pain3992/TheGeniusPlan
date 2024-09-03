// MyHttpHelper.h

#pragma once

#include "CoreMinimal.h"
#include "Http.h"

// 콜백 함수의 형태를 정의
// DECLARE_DELEGATE_ThreeParams(FHttpResponseDelegate, FHttpRequestPtr, FHttpResponsePtr, bool);
DECLARE_DELEGATE_ThreeParams(FHttpResponseDelegate, bool /*bWasSuccessful*/, TSharedPtr<FJsonObject> /*JsonResponse*/, const FString& /*ErrorMessage*/);

class THEGENIUSPLAN_API UHttpRequstHelper
{
public:
	// HTTP 메서드를 받는 헬퍼 함수
	static void SendHttpRequest(const FString& Url, const TSharedPtr<FJsonObject> JsonObject, const FString& Verb, FHttpResponseDelegate ResponseDelegate);
	// GET 요청을 위한 함수
	static void SendGetRequest(const FString& Url, FHttpResponseDelegate ResponseDelegate);
	// POST 요청을 위한 함수
	static void SendPostRequest(const FString& Url, const TSharedPtr<FJsonObject> JsonObject, FHttpResponseDelegate ResponseDelegate);
	// PATCH 요청을 위한 함수
	static void SendPatchRequest(const FString& Url, const TSharedPtr<FJsonObject> JsonObject, FHttpResponseDelegate ResponseDelegate);
	// DELETE 요청을 위한 함수
	static void SendDeleteRequest(const FString& Url, FHttpResponseDelegate ResponseDelegate);
private:
	static void HandleResponse(FHttpResponsePtr Response, bool bWasSuccessful, FHttpResponseDelegate ResponseDelegate);
};
