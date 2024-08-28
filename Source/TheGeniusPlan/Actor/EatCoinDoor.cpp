#include "EatCoinDoor.h"
#include "Components/TimelineComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AEatCoinDoor::AEatCoinDoor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEatCoinDoor::BeginPlay()
{
    Super::BeginPlay();

    // 초기 위치 저장
    InitialLocation = GetActorLocation();
    // 문이 목표로 하는 위치 설정 (위로 300 유닛 올라가도록 설정)
    TargetLocation = InitialLocation + FVector(0, 0, 300.0f);
}

void AEatCoinDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEatCoinDoor::StartOpening()
{
    // 문을 여는 타이머 시작 (0.01초마다 호출)
    GetWorld()->GetTimerManager().SetTimer(DoorOpeningTimerHandle, this, &AEatCoinDoor::OpenDoorStep, 0.01f, true);
}

void AEatCoinDoor::OpenDoorStep()
{
    FVector CurrentLocation = GetActorLocation();
    // 문이 목표 위치에 도달했는지 확인
    if (CurrentLocation.Z >= TargetLocation.Z)
    {
        // 타이머 종료
        GetWorld()->GetTimerManager().ClearTimer(DoorOpeningTimerHandle);

        // 문이 다 열린 후 일정 시간 대기 후 닫기 시작
        GetWorld()->GetTimerManager().SetTimer(DoorOpenWaitHandle, this, &AEatCoinDoor::StartClosing, 5.0f, false);  // 5초 대기
        return;
    }

    // 문을 조금씩 올림 (속도 조정 가능)
    FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, GetWorld()->GetDeltaSeconds(), 200.0f);
    SetActorLocation(NewLocation);
}

void AEatCoinDoor::StartClosing()
{
    // 문을 닫는 타이머 시작 (0.01초마다 호출)
    GetWorld()->GetTimerManager().SetTimer(DoorClosingTimerHandle, this, &AEatCoinDoor::CloseDoorStep, 0.01f, true);
}

void AEatCoinDoor::CloseDoorStep()
{
    FVector CurrentLocation = GetActorLocation();
    // 문이 초기 위치에 도달했는지 확인
    if (CurrentLocation.Z <= InitialLocation.Z)
    {
        // 타이머 종료
        GetWorld()->GetTimerManager().ClearTimer(DoorClosingTimerHandle);
        return;
    }

    // 문을 조금씩 내림 (속도 조정 가능)
    FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, InitialLocation, GetWorld()->GetDeltaSeconds(), 200.0f);
    SetActorLocation(NewLocation);
}
