// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility_SingleTarget.h"
#include "DRAbility_BasicAttack.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_BasicAttack : public UDRAbility_SingleTarget
{
	GENERATED_BODY()
public:
	virtual void Use() override;
	bool TrySetTarget(UDRAbilityTargetComponent* target);
protected:
	UPROPERTY(EditDefaultsOnly, Category= "DRAbility")
	int mDamage;
};
