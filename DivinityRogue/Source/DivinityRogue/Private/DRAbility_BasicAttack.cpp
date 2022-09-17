// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_BasicAttack.h"
#include "DRCharacter.h"

void UDRAbility_BasicAttack::Use()
{
	Super::Use();
	const FDamageEvent damageEvent;
	mTarget->TakeDamage(mDamage, damageEvent, mOwner->GetController(), mOwner);
}
