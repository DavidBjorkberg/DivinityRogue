// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "GameFramework/PlayerController.h"
#include "DRPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API ADRPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADRPlayerController();
protected:
	virtual void SetupInputComponent() override;
	UFUNCTION()
	void OnLeftMouseClick();
};
