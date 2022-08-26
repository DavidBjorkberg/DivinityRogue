// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility.h"

#include "DRCharacter.h"

void UDRAbility::Use(ADRCharacter* user, ADRCharacter* target)
{
	user->ConsumeActionPoints(mActionPointCost);
}

bool UDRAbility::CanCast(ADRCharacter* user, ADRCharacter* target)
{
	return IsInRange(user, target) &&
		IsValidTarget(user, target) &&
		user->GetCurrentActionPoints() >= mActionPointCost;
}

bool UDRAbility::IsInRange(ADRCharacter* user, ADRCharacter* target)
{
	float distanceToTarget = FVector::Dist2D(user->GetActorLocation(), target->GetActorLocation());
	return distanceToTarget <= mRange;
}

bool UDRAbility::IsValidTarget(ADRCharacter* user, ADRCharacter* target)
{
	switch (mTargetType)
	{
	case TargetType::ENEMY:
		return user->GetTeam() != target->GetTeam();
		break;
	case TargetType::ALLY:
		return user->GetTeam() == target->GetTeam() || target->GetTeam() == ETeam::NEUTRAL;
		break;
	case TargetType::ANY:
		return true;
		break;
	default:
		return false;
	}
}
