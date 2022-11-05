// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Whirlwind.h"

#include "DRGameplayStatics.h"

void UDRAbility_Whirlwind::Use()
{
	Super::Use();
	TArray<UDRAbilityTargetComponent*> abilityTargetsInRange = UDRGameplayStatics::GetAllAbilityTargetsInRadius(
		mWorld,
		mOwner->GetActorLocation(),
		mAbilityInfo.mRange);
	
	for (UDRAbilityTargetComponent* AbilityTargetInRange : abilityTargetsInRange)
	{
		if (IsValidTarget(AbilityTargetInRange))
		{
			AbilityTargetInRange->TakeDamage(mDamage, mOwner);
		}
	}
}
