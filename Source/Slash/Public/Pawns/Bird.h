// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UFloatingPawnMovement;
class UCapsuleComponent;
class USkeletalMeshComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class SLASH_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Move action handlers
	UFUNCTION(BlueprintCallable, Category="Input")
	void Move(const FInputActionValue& Value);

	// Look action handlers
	UFUNCTION(BlueprintCallable, Category="Input")
	void Look(const FInputActionValue& Value);

	// JumpStart action handlers
	UFUNCTION(BlueprintCallable, Category="Input")
	void JumpStart(const FInputActionValue& Value);

	// JumpEnd action handlers
	UFUNCTION(BlueprintCallable, Category="Input")
	void JumpEnd(const FInputActionValue& Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* JumpAction;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UCapsuleComponent* Capsule = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* BirdMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UFloatingPawnMovement* FloatingMovement = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera = nullptr;
};
