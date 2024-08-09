// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheGeniusPlanController.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API ATheGeniusPlanController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	ATheGeniusPlanController();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<class UChatComponent> ChatComponent;


protected:
	
};
