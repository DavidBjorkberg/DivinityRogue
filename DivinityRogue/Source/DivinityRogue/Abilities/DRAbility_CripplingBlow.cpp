// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_CripplingBlow.h"
#include "DRGameplayStatics.h"

void UDRAbility_CripplingBlow::Use()
{
	Super::Use();
	mTarget->TakeDamage(mDamage, mOwner);
	TArray<UDRAbilityTargetComponent*> nearbyTargets = GetNearbyTargets();
	for (int i = nearbyTargets.Num() - 1; i >= 0; i--)
	{
		nearbyTargets[i]->TakeDamage(mDamage, mOwner);
		//TODO: Apply cripple
	}
}

bool UDRAbility_CripplingBlow::AIShouldUse()
{
	return Super::AIShouldUse();
}
