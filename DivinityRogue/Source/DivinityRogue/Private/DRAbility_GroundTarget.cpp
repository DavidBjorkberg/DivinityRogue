// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_GroundTarget.h"

#include "DRGameplayStatics.h"
#include "NavigationSystem.h"

void UDRAbility_GroundTarget::OnLeftMouseDown()
{
	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		FVector walkableGroundUnderCursor;
		if (UDRGameplayStatics::GetWalkableGroundPositionUnderCursor(GetWorld(), walkableGroundUnderCursor))
		{
			mTargetLocation = walkableGroundUnderCursor;
			mGameMode->GetCharacterInPlay()->PlayAttackAnimation(this);
		}
		mGameMode->SetSelectedAbility(-1);
		mGameMode->SetGameplayState(EGameplayState::PlanningPath);
	}
}

bool UDRAbility_GroundTarget::TrySetRandomTargets()
{
	FNavLocation randomLocation;

	if (UNavigationSystemV1::GetCurrent(GetWorld())->GetRandomPointInNavigableRadius(
		mOwner->GetActorLocation(), mAbilityInfo.mRange, randomLocation))
	{
		mTargetLocation = randomLocation.Location;
		return true;
	}
	return false;
}

bool UDRAbility_GroundTarget::CanCast()
{
	return mTargetLocation != FVector::ZeroVector && CanAffordCast();
}

void UDRAbility_GroundTarget::ClearSelection()
{
	mTargetLocation = FVector::ZeroVector;
}
