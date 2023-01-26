// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_NoTarget_AOE.h"

#include "DRGameplayStatics.h"

bool UDRAbility_NoTarget_AOE::TrySetRandomTargets()
{
	mTargets = UDRGameplayStatics::GetAllAbilityTargetsInRadius(GetWorld(), mOwner->GetActorLocation(), GetRange());
	for (int i = mTargets.Num() - 1; i >= 0; i--)
	{
		if (GetAbilityInfo().mTargetType == TargetType::ANY)
		{
			break;
		}
		if(!IsTargetCorrectTeam(mTargets[i]))
		{
			mTargets.RemoveAt(i);
		}
	}
	return true;
}
