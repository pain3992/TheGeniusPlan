// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Actor/GyulhapCube.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AGyulhapCube::AGyulhapCube()
{
	PrimaryActorTick.bCanEverTick = true;

    // Create the static mesh component and attach it to the root
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    RootComponent = StaticMeshComponent;

    // Load and add static meshes to the array
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh1(TEXT("StaticMesh'/Game/JiYoung/Gyulhap/StaticMesh/SM_B_Lightning_G.SM_B_Lightning_G'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh2(TEXT("StaticMesh'/Game/JiYoung/Gyulhap/StaticMesh/SM_B_Lightning_P.SM_B_Lightning_P'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh3(TEXT("StaticMesh'/Game/JiYoung/Gyulhap/StaticMesh/SM_B_Lightning_S.SM_B_Lightning_S'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh4(TEXT("StaticMesh'/Game/JiYoung/Gyulhap/StaticMesh/SM_B_Star_G.SM_B_Star_G'"));

    // Add the meshes to the array if they were successfully loaded
    if (Mesh1.Succeeded()) StaticMeshes.Add(Mesh1.Object);
    if (Mesh2.Succeeded()) StaticMeshes.Add(Mesh2.Object);
    if (Mesh3.Succeeded()) StaticMeshes.Add(Mesh3.Object);
    if (Mesh4.Succeeded()) StaticMeshes.Add(Mesh4.Object);
    // Continue for all 27 meshes
}

void AGyulhapCube::BeginPlay()
{
    Super::BeginPlay();

    // Ensure the work is done in the game thread
    if (IsInGameThread())
    {
        SelectRandomMesh();
    }
}

void AGyulhapCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGyulhapCube::SelectRandomMesh()
{
    if (StaticMeshes.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, StaticMeshes.Num() - 1);
        UStaticMesh* SelectedMesh = StaticMeshes[RandomIndex];
        if (SelectedMesh)
        {
            StaticMeshComponent->SetStaticMesh(SelectedMesh);
            StaticMeshComponent->SetSimulatePhysics(true); // Enable physics
        }
    }
}

