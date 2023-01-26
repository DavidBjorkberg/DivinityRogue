// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility_SingleTarget.h"
#include "DRAbility_Charge.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_Charge : public UDRAbility_SingleTarget
{
	GENERATED_BODY()
public:
	virtual void Use() override;
	virtual bool AIShouldUse() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	int mDamage;
	UPROPERTY(EditDefaultsOnly, Category= "AI")
	float mMinimumDistance;
};
