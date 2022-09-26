// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_ShadowStep.h"

void UDRAbility_ShadowStep::Use()
{
	Super::Use();
	FVector targetLocation = mTarget->GetActorLocation();
	FVector targetRotation = mTarget->GetActorRotation().Vector();
	FVector behindTargetLocation = targetLocation - (targetRotation * 150);
	mOwner->SetActorLocation(behindTargetLocation);
	const FDamageEvent damageEvent;

	mTarget->TakeDamage(mDamage, damageEvent, mOwner->GetController(), mOwner);
}
