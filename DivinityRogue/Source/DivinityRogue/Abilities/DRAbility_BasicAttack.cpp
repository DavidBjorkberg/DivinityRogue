// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_BasicAttack.h"
#include "DRCharacter.h"

void UDRAbility_BasicAttack::Use()
{
	Super::Use();
	mTarget->TakeDamage(mDamage, mOwner);
}

bool UDRAbility_BasicAttack::TrySetTarget(UDRAbilityTargetComponent* target)
{
	if (target->GetTeam() != mOwner->GetAbilityTargetComponent()->GetTeam())
	{
		mTarget = target;
		return true;
	}
	return false;
}
