// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_SingleTarget_Bounce.h"

#include "DRGameplayStatics.h"

TArray<UDRAbilityTargetComponent*> UDRAbility_SingleTarget_Bounce::GetBounceTargets()
{
	TArray<UDRAbilityTargetComponent*> bounceTargets;
	UDRAbilityTargetComponent* previousJumpTarget = mTarget;
	for (int i = 0; i < mNrOfBounces; i++)
	{
		TArray<UDRAbilityTargetComponent*> targetsInBounceRange = GetAllValidTargetsInRadius(
			previousJumpTarget->GetOwner()->GetActorLocation(), mBounceRange, true);

		for (int j = targetsInBounceRange.Num() - 1; j >= 0; j--)
		{
			if (bounceTargets.Contains(targetsInBounceRange[i]))
			{
				targetsInBounceRange.RemoveAt(j);
			}
		}

		if (targetsInBounceRange.Num() == 0)
		{
			break;
		}

		UDRGameplayStatics::SortComponentListByDistance(previousJumpTarget->GetOwner(), targetsInBounceRange);
		bounceTargets.Add(targetsInBounceRange[0]);
		previousJumpTarget = targetsInBounceRange[0];
	}
	return bounceTargets;
}
