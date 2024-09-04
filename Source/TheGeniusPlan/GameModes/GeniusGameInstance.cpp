// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/GameModes/GeniusGameInstance.h"

void UGeniusGameInstance::SetLoginInfo(const FLoginInfo& NewLoginInfo)
{
	LoginInfo = NewLoginInfo;
	OnLoginInfoUpdated.Broadcast(LoginInfo);
}
