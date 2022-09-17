// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_MultiShot.h"

void UDRAbility_MultiShot::Use()
{
	Super::Use();

	for (auto target : mTargetedCharacters)
	{
		const FDamageEvent damageEvent;
		target->TakeDamage(mDamage, damageEvent, mOwner->GetController(), mOwner);
	}
}
