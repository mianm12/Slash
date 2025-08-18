// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Bird.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABird::ABird()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create and configure the capsule component
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Capsule->SetCollisionObjectType(ECC_Pawn);
	Capsule->SetCollisionResponseToAllChannels(ECR_Block);
	Capsule->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	Capsule->SetCapsuleHalfHeight(20.f);
	Capsule->SetCapsuleRadius(15.f);
	SetRootComponent(Capsule);

	// Create and configure the skeletal mesh component
	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(Capsule);

	// Create and configure the floating pawn movement component
	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	FloatingMovement->UpdatedComponent = Capsule;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Capsule);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom
	FollowCamera->bUsePawnControlRotation = false; // Don't rotate the camera with the controller, use the boom's rotation instead
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
}

void ABird::Move(const FInputActionValue& Value)
{
	if (GetController() != nullptr)
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		const float Forward = MovementVector.Y;
		const float Right = MovementVector.X;

		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ABird::Look(const FInputActionValue& Value)
{
	if (GetController() != nullptr)
	{
		const FVector2D LookAxisVector = Value.Get<FVector2D>();
		const float Yaw = LookAxisVector.X;
		const float Pitch = LookAxisVector.Y;

		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ABird::JumpStart(const FInputActionValue& Value)
{
}

void ABird::JumpEnd(const FInputActionValue& Value)
{
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABird::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ABird::JumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABird::JumpEnd);
	}
}
