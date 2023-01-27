// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_SingleTarget_AOE.h"

#include "DRGameplayStatics.h"
#include "DRPlayerController.h"


bool UDRAbility_SingleTarget_AOE::TrySetRandomTargets()
{
	Super::TrySetRandomTargets();
	if(mTarget == nullptr)
	{
		return false;
	}

	mNearbyTargets = UDRGameplayStatics::GetAllAbilityTargetsInRadius(
	GetWorld(), mTarget->GetOwner()->GetActorLocation(), mRadius);
	mNearbyTargets.Remove(mTarget);
	for (int i = mNearbyTargets.Num() - 1; i >= 0; i--)
	{
		if (!IsTargetCorrectTeam(mNearbyTargets[i]))
		{
			mNearbyTargets.RemoveAt(i);
		}
	}
	return true;
}
