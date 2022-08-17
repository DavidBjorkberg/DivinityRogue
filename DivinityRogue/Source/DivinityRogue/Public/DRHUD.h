// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRCharacter.h"
#include "GameFramework/HUD.h"
#include "DRHUD.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API ADRHUD : public AHUD
{
	GENERATED_BODY()
public:
	void StartTargeting(ADRCharacter* character, ADRAbility* ability);
	void StopTargeting();
	virtual void DrawHUD() override;

private:
	UPROPERTY()
	ADRAbility* mTargetingAbility;
	UPROPERTY()
	ADRCharacter* mCharacterUsingAbility;
};
