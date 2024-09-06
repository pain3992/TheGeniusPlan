// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheGeniusPlanCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TheGeniusPlan/ChatComponent.h"
#include "TheGeniusPlan/Widget/ChatWidget.h"
#include "TheGeniusPlan/Player/GeniusPlayerController.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "TheGeniusPlan/Widget/MainGame/HelpUserWidget.h"
#include "InputMappingContext.h"
#include "TheGeniusPlan/Player/MainHallPlayerController.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATheGeniusPlanCharacter

ATheGeniusPlanCharacter::ATheGeniusPlanCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	ATheGeniusPlanCharacter::SetReplicateMovement(true);

	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;			 // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;		// The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;								// Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	bCanMove = true;
}

void ATheGeniusPlanCharacter::changeCameraMode()
{
	if (CameraBoom->TargetArmLength > 0.0)
	{
		CameraBoom->TargetArmLength = 0.0f;
	}
	else
	{
		CameraBoom->TargetArmLength = 400.0f;
	}
}

void ATheGeniusPlanCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATheGeniusPlanCharacter::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();

	if (HasAuthority())
	{
		UE_LOG(LogTemp, Log, TEXT("Character has authority on the server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Character is replicating on the client"));
	}

	// 중요한 컴포넌트가 초기화되었는지 확인
	if (!FollowCamera || !CameraBoom)
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera components are not initialized"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Camera components are initialized"));
	}

	// 중요한 액션이 초기화되었는지 확인
	if (!JumpAction || !MoveAction || !LookAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input actions are not initialized"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Input actions are initialized"));
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATheGeniusPlanCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	UInputMappingContext* NewIMC = LoadObject<UInputMappingContext>(nullptr, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/ThirdPerson/Input/IMC_Default.IMC_Default'"));
	// Add Input Mapping Context
	if (APlayerController *PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(NewIMC, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATheGeniusPlanCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATheGeniusPlanCharacter::Look);
		EnhancedInputComponent->BindAction(ChatFocusAction, ETriggerEvent::Started, this, &ATheGeniusPlanCharacter::ChatFocus);

		EnhancedInputComponent->BindAction(HintAction, ETriggerEvent::Triggered, this, &ATheGeniusPlanCharacter::Hint);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATheGeniusPlanCharacter::Move(const FInputActionValue &Value)
{
	if (bCanMove)
	{
		// input is a Vector2D
		FVector2D MovementVector = Value.Get<FVector2D>();

		if (Controller != nullptr)
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			// get right vector
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// add movement
			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
		}
	}
}

void ATheGeniusPlanCharacter::Look(const FInputActionValue &Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput((LookAxisVector.Y));
	}
}

void ATheGeniusPlanCharacter::ChatFocus(const FInputActionValue &Value)
{
	UE_LOG(LogTemp, Error, TEXT("Pressed Enter"));
	bool bIsEnter = Value.Get<bool>();

	if (bIsEnter)
	{
		AMainHallPlayerController* myController = Cast<AMainHallPlayerController>(GetController());
		if (myController->ChatComponent->GetChatVaild())
		{
			myController->ChatComponent->ChatWidget->FocusChatWidget();
			UE_LOG(LogTemp, Error, TEXT("Focus ChatWidget"));
		}

		UE_LOG(LogTemp, Error, TEXT("Chat is Not Vaild"));
	}
	
}

void ATheGeniusPlanCharacter::Hint(const FInputActionValue &Value)
{
	bool bIsHintPressed = Value.Get<bool>();

	if (bIsHintPressed)
	{
		APlayerController *PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			AMainGameHUD *HUD = Cast<AMainGameHUD>(PlayerController->GetHUD());
			if (HUD && HUD->GetHelpWidget())
			{
				// Toggle the visibility of the HelpWidget
				UHelpUserWidget *HelpWidget = HUD->GetHelpWidget();
				if (HUD->GetHelpWidget()->IsVisible())
				{
					HUD->ShowWidget(MainGameWidgetType::NONE); // Hide HelpWidget
				}
				else
				{
					HUD->ShowWidget(MainGameWidgetType::HelpWidget); // Show HelpWidget
				}
			}
		}
	}
}
