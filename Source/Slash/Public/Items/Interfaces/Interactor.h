﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactor.generated.h"

class IInteractable;

// This class does not need to be modified.
UINTERFACE()
class UInteractor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SLASH_API IInteractor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * @brief Function to get the currently focused interactable object
	 * 
	 * @return TScriptInterface<IInteractable> The currently focused interactable object
	 */
	virtual TScriptInterface<IInteractable> GetFocusedInteractable() const = 0;
};
