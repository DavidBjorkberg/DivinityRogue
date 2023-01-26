// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_MultiShot.h"

#include "DRCharacter.h"

void UDRAbility_MultiShot::Use()
{
	Super::Use();

	for (auto target : mTargets)
	{
		target->TakeDamage(mDamage, mOwner);
	}
}

bool UDRAbility_MultiShot::AIShouldUse()
{
	return Super::AIShouldUse();
}
