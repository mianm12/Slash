// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Items/Interfaces/Interactor.h"
#include "SlashCharacter.generated.h"

class IInteractable;
class UGroomComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;

struct FInputActionValue;

UCLASS()
class SLASH_API ASlashCharacter : public ACharacter, public IInteractor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlashCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// JumpStart action handlers
	UFUNCTION(BlueprintCallable, Category="Input")
	void JumpStart(const FInputActionValue& Value);

	// JumpEnd action handlers
	UFUNCTION(BlueprintCallable, Category="Input")
	void JumpEnd(const FInputActionValue& Value);

	// Look action handlers
	UFUNCTION(BlueprintCallable, Category="Input")
	void Look(const FInputActionValue& Value);

	// Move action handlers
	UFUNCTION(BlueprintCallable, Category="Input")
	void Move(const FInputActionValue& Value);

	// Equip action handlers
	UFUNCTION(BlueprintCallable, Category="Input")
	void Interact(const FInputActionValue& Value);
	
	FORCEINLINE virtual TScriptInterface<IInteractable> GetFocusedInteractable() const override { return FocusedInteractable; };
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> InteractAction;

	void CheckForInteractable();

	UPROPERTY(EditAnywhere, Category="Interaction")
	float InteractionDistance = 200.f;
	
	UPROPERTY(EditAnywhere, Category="Interaction")
	float InteractionSphereRadius = 30.f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hair", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UGroomComponent> Hair = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hair", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UGroomComponent> Eyebrows = nullptr;

	// Currently focused interactable object
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	TScriptInterface<IInteractable> FocusedInteractable;
};
