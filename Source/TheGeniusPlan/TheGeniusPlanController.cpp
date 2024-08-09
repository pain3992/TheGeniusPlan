// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlanController.h"
#include "TheGeniusPlan/ChatComponent.h"

void ATheGeniusPlanController::BeginPlay()
{

}

ATheGeniusPlanController::ATheGeniusPlanController()
{
	ChatComponent = CreateDefaultSubobject<UChatComponent>(TEXT("ChatComponent"));

	if (ChatComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ChatComponent Create Succeeded!"));
	}
}
