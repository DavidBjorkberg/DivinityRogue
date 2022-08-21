// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAbility_BasicAttack.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRAbility_BasicAttack : public UDRAbility
{
	GENERATED_BODY()	
public:
	virtual bool TryUse(ADRCharacter* user, ADRCharacter* target) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category= "DRAbility")
	int mDamage;
};
