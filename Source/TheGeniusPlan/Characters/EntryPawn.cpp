// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Characters/EntryPawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AEntryPawn::AEntryPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SelectedSkeletaMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SelectedSkeletaMesh->SetupAttachment(RootComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(SelectedSkeletaMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	CameraBoom->SetRelativeLocation(FVector(0, 0, 80));
	CameraBoom->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	USkeletalMesh* Men = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	USkeletalMesh* Woman = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));

	if (Men)
	{
		SkeletalMeshes.Add(Men);
	}

	if(Woman)
	{
		SkeletalMeshes.Add(Woman);
	}

	if (SkeletalMeshes.Num() > 0)
	{
		SelectedSkeletaMesh->SetSkeletalMesh(SkeletalMeshes[0]);
		// SelectedSkeletaMesh->SetRelativeRotation(FRotator(0.0, 90.0, 0.0));
		// SelectedSkeletaMesh->SetRelativeLocation(FVector(0.0, 0.0, -90.0));
	}

	UClass* MenAnimBlueprint = LoadObject<UClass>(nullptr, TEXT("/Script/Engine.AnimBlueprint'/Game/Characters/Mannequins/Animations/ABP_Quinn.ABP_Quinn_C'"));

	if (MenAnimBlueprint)
	{
		SelectedSkeletaMesh->SetAnimClass(Cast<UAnimBlueprintGeneratedClass>(MenAnimBlueprint));
		bIsMen = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimBlueprint is Null"));
	}

}

void AEntryPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AEntryPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEntryPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEntryPawn::ChangeMesh()
{
	UClass* MenAnimBlueprint = LoadObject<UClass>(nullptr, TEXT("/Script/Engine.AnimBlueprint'/Game/Characters/Mannequins/Animations/ABP_Manny.ABP_Manny_C'"));
	UClass* WomanAnimBlueprint = LoadObject<UClass>(nullptr, TEXT("/Script/Engine.AnimBlueprint'/Game/Characters/Mannequins/Animations/ABP_Quinn.ABP_Quinn_C'"));

	if(!bIsMen)
	{
		SelectedSkeletaMesh->SetSkeletalMesh(SkeletalMeshes[0]);
		SelectedSkeletaMesh->SetAnimClass(Cast<UAnimBlueprintGeneratedClass>(MenAnimBlueprint));
		bIsMen = true;
	}
	else
	{
		SelectedSkeletaMesh->SetSkeletalMesh(SkeletalMeshes[1]);
		SelectedSkeletaMesh->SetAnimClass(Cast<UAnimBlueprintGeneratedClass>(WomanAnimBlueprint));
		bIsMen = false;
	}
}
