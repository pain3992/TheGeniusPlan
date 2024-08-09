#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEGENIUSPLAN_API UChatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UChatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ChatWidgetClass")
	TSubclassOf<class UChatWidget> ChatWidgetClass;

	UPROPERTY()
	bool bIsChatVaild;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ChatWidget")
	TObjectPtr<class UChatWidget> ChatWidget;

	UFUNCTION()
	void CreateChatWidget();

	UFUNCTION()
	void RemoveChatWidget();

	UFUNCTION()
	bool GetChatVaild();

	UFUNCTION(Server, Reliable)
	void SendMyMessage(const FString& Message);

	UFUNCTION(Client, Reliable)
	void AddMyChatMessage(const FString& Message);
		
};
