// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlashAnimInstance.generated.h"

class UCharacterMovementComponent;
class ASlashCharacter;
/**
 * 
 */
UCLASS()
class SLASH_API USlashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeUpdateAnimation(float DeltaTimeRPM) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ASlashCharacter* SlashCharacter = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCharacterMovementComponent* MovementComponent = nullptr;

	/// @brief The horizontal speed squared of the character's movement.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
	float HorizontalSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
	bool bIsFalling = false;
};
