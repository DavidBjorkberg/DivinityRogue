// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRGameMode.h"
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
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	void StartTargeting(ADRCharacter* character, ADRAbility* ability);
	void StopTargeting();
private:
	UPROPERTY()
	ADRAbility* mTargetingAbility;
	UPROPERTY()
	ADRCharacter* mCharacterUsingAbility;
	UPROPERTY()
	ADRGameMode* mGameMode;
};
