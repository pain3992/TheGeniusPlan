
#include "ChatRoomActor.h"
#include "Components/BoxComponent.h"
#include "TheGeniusPlanCharacter.h"
#include "TheGeniusPlan/Player/GeniusPlayerController.h"
#include "ChatComponent.h"



AChatRoomActor::AChatRoomActor()
{

	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetBoxExtent(FVector(50.0, 50.0, 50.0));
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AChatRoomActor::OnComponentBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AChatRoomActor::OnComponentEndOverlap);

}

void AChatRoomActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChatRoomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChatRoomActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* OverlapActor = Cast<ACharacter>(OtherActor);

	if(OverlapActor)
	{

		if (OverlapActor->GetController() == GetWorld()->GetFirstPlayerController())
		{
			AGeniusPlayerController* PlayerController = Cast<AGeniusPlayerController>(OverlapActor->GetController());

			if (PlayerController)
			{
				PlayerController->ChatComponent->CreateChatWidget((uint8)thisRoomType);
			}
		}
	}
}

void AChatRoomActor::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	ACharacter* OverlapActor = Cast<ACharacter>(OtherActor);

	if (OverlapActor)
	{
		AGeniusPlayerController* PlayerController = Cast<AGeniusPlayerController>(OverlapActor->GetController());

		if (PlayerController)
		{
			PlayerController->ChatComponent->RemoveChatWidget();
		}
	}
}

