// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_CripplingBlow.h"

#include "DRAbility_Slam.h"

#include "DRGameplayStatics.h"

void UDRAbility_CripplingBlow::Use()
{
	Super::Use();
	mTarget->TakeDamage(mDamage, mOwner);
	for (int i = mNearbyTargets.Num() - 1; i >= 0; i--)
	{
		if (IsTargetCorrectTeam(mNearbyTargets[i]))
		{
			mNearbyTargets[i]->TakeDamage(mDamage, mOwner);
			//TODO: Apply cripple
		}
	}
}

bool UDRAbility_CripplingBlow::AIShouldUse()
{
	return Super::AIShouldUse();
}
