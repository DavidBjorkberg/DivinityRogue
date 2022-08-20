// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility.h"

#include "DRCharacter.h"

bool UDRAbility::TryUse(ADRCharacter* user, ADRCharacter* target)
{
	return false;
}

bool UDRAbility::IsInRange(ADRCharacter* user,ADRCharacter* target)
{
	float distanceToTarget = FVector::Dist2D(user->GetActorLocation(),target->GetActorLocation());
	return distanceToTarget <= mRange;
}
