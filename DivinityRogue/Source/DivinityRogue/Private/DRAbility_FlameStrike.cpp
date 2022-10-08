// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_FlameStrike.h"

void UDRAbility_FlameStrike::Use()
{
	Super::Use();
	FDamageEvent damageEvent;
	for (auto target : mTargets)
	{
		target->TakeDamage(mDamage,damageEvent,mOwner->GetController(),mOwner);
	}
}
