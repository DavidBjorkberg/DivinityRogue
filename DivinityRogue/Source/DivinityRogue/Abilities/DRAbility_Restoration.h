// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility_SingleTarget.h"
#include "DRAbility_Restoration.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_Restoration : public UDRAbility_SingleTarget
{
	GENERATED_BODY()
public:
	virtual void Use() override;
	virtual bool AIShouldUse() override;
	virtual bool TrySetRandomTargets() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	int mHealing;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	float mTargetMaximumHealthPercent;
};
