// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/GameModes/GeniusGameInstance.h"

void UGeniusGameInstance::SetLoginInfo(const FLoginInfo& NewLoginInfo)
{
	LoginInfo = NewLoginInfo;
	OnLoginInfoUpdated.Broadcast(LoginInfo);
}

UGeniusGameInstance::UGeniusGameInstance()
{
	Number = 0;
	UE_LOG(LogTemp, Error, TEXT("First : %d"), Number);

}

void UGeniusGameInstance::SetWinnerPlayer()
{

}

void UGeniusGameInstance::PrintWinnerPlayer()
{
	UE_LOG(LogTemp, Error, TEXT("Second : %d"), Number);
}
