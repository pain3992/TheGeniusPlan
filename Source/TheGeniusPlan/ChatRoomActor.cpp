
#include "ChatRoomActor.h"
#include "Components/BoxComponent.h"
#include "TheGeniusPlanCharacter.h"
#include "TheGeniusPlanController.h"
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
	UE_LOG(LogTemp, Error, TEXT("BeginOverlap"));
	ACharacter* OverlapActor = Cast<ACharacter>(OtherActor);

	if(OverlapActor)
	{
		UE_LOG(LogTemp, Error, TEXT("OverlapActor Cast Succeeded!"));

		if (OverlapActor->GetController() == GetWorld()->GetFirstPlayerController())
		{
			ATheGeniusPlanController* PlayerController = Cast<ATheGeniusPlanController>(OverlapActor->GetController());

			if (PlayerController)
			{
				UE_LOG(LogTemp, Error, TEXT("PlayerController Cast Succeeded!"));
				PlayerController->ChatComponent->CreateChatWidget((uint8)thisRoomType);
			}
		}
	}
}

void AChatRoomActor::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Error, TEXT("EndOverlap"));

	ACharacter* OverlapActor = Cast<ACharacter>(OtherActor);

	if (OverlapActor)
	{
		UE_LOG(LogTemp, Error, TEXT("OverlapActor Cast Succeeded!"));
		ATheGeniusPlanController* PlayerController = Cast<ATheGeniusPlanController>(OverlapActor->GetController());

		if (PlayerController)
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerController Cast Succeeded!"));
			PlayerController->ChatComponent->RemoveChatWidget();
		}
	}
}

