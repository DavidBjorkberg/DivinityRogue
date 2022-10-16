// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility_NoTarget.h"
#include "DRAbility_Whirlwind.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_Whirlwind : public UDRAbility_NoTarget
{
	GENERATED_BODY()
public:
	virtual void Use() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	int mDamage;
};