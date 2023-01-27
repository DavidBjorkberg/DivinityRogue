// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Leap.h"

#include "DRCharacter.h"
#include "DRGameplayStatics.h"
#include "NavigationSystem.h"

void UDRAbility_Leap::Use()
{
	Super::Use();
	FVector startLocation = mOwner->GetActorLocation();
	mOwner->FindComponentByClass<UDRAbilityTargetComponent>()->TeleportTo(mTargetLocation);
	UDRGameplayStatics::PlaySoundAtLocation(GetWorld(), mOnUsedSound, startLocation);
	UDRGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mOnUsedParticleEffect, startLocation);
}

bool UDRAbility_Leap::AIShouldUse()
{
	UDRAbilityTargetComponent* closestEnemyTarget = UDRGameplayStatics::GetClosestEnemyTarget(
		GetWorld(), mOwner);
	float distance = UDRGameplayStatics::GetDistanceToEdge2D(mOwner->GetActorLocation(), closestEnemyTarget);
	return distance <= mUseAbilityDistanceThreshold;
}

bool UDRAbility_Leap::TrySetRandomTargets()
{
	for (int i = 0; mFindLocationAttempts; i++)
	{
		FNavLocation randomLocation;
		if (UNavigationSystemV1::GetCurrent(GetWorld())->GetRandomPointInNavigableRadius(
			mOwner->GetActorLocation(), mAbilityInfo.mRange, randomLocation))
		{
			UDRAbilityTargetComponent* closestEnemyTarget = UDRGameplayStatics::GetClosestEnemyTargetFromLocation(
				GetWorld(), mOwner, randomLocation.Location);
			float distance = UDRGameplayStatics::GetDistanceToEdge2D(mOwner->GetActorLocation(), closestEnemyTarget);
			if (distance >= mMinimumDistanceToClosestEnemy)
			{
				mTargetLocation = randomLocation.Location;
				return true;
			}
		}
	}
	return false;
}
