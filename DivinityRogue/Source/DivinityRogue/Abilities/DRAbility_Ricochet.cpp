// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Ricochet.h"
#include "DRGameplayStatics.h"

void UDRAbility_Ricochet::Use()
{
	Super::Use();
	mTarget->TakeDamage(mDamage, mOwner);
	TArray<UDRAbilityTargetComponent*> bounceTargets = GetBounceTargets();
	for (int i = bounceTargets.Num() - 1; i >= 0; i--)
	{
		bounceTargets[i]->TakeDamage(mDamage, mOwner);
	}
}

bool UDRAbility_Ricochet::AIShouldUse()
{
	return Super::AIShouldUse();
}
