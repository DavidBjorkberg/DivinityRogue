// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_SingleTarget_AOE.h"

#include "DRGameplayStatics.h"
#include "DRPlayerController.h"

TArray<UDRAbilityTargetComponent*> UDRAbility_SingleTarget_AOE::GetNearbyTargets()
{
	TArray<UDRAbilityTargetComponent*> nearbyTargets = UDRGameplayStatics::GetAllAbilityTargetsInRadius(
		GetWorld(), mTarget->GetOwner()->GetActorLocation(), mRadius);
	nearbyTargets.Remove(mTarget);
	for (int i = nearbyTargets.Num() - 1; i >= 0; i--)
	{
		if (!IsTargetCorrectTeam(nearbyTargets[i]))
		{
			nearbyTargets.RemoveAt(i);
		}
	}
	return nearbyTargets;
}
