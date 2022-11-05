// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_FlameStrike.h"

#include "DRCharacter.h"

void UDRAbility_FlameStrike::Use()
{
	Super::Use();
	for (auto target : mTargets)
	{
		target->TakeDamage(mDamage, mOwner);
	}
}
