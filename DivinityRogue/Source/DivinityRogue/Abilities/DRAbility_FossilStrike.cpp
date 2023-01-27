// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_FossilStrike.h"

#include "DRGameplayStatics.h"

void UDRAbility_FossilStrike::Use()
{
	Super::Use();
	mTarget->TakeDamage(mDamage, mOwner);
}

bool UDRAbility_FossilStrike::AIShouldUse()
{
	return TrySetRandomTargets();
}
