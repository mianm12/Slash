// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SlashAnimInstance.h"

#include "Character/SlashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void USlashAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();


	SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());
	if (SlashCharacter)
	{
		MovementComponent = SlashCharacter->GetCharacterMovement();
	}
	
}

void USlashAnimInstance::NativeUpdateAnimation(float DeltaTimeRPM)
{
	Super::NativeUpdateAnimation(DeltaTimeRPM);

	if (MovementComponent)
	{
		HorizontalSpeed = MovementComponent->Velocity.SizeSquared2D();
		bIsFalling = MovementComponent->IsFalling();
		CharacterState = SlashCharacter->GetCharacterState();
	}
}
