// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_BasicAttack.h"
#include "DRCharacter.h"

void UDRAbility_BasicAttack::Use()
{
	Super::Use();
	mTarget->TakeDamage(mDamage,mOwner);
}

void UDRAbility_BasicAttack::SetTarget(UDRAbilityTargetComponent* target)
{
	mTarget = target;
}
