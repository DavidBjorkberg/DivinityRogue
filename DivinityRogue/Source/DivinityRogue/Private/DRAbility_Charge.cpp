// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Charge.h"

#include "DRCharacter.h"

void UDRAbility_Charge::Use()
{
	Super::Use();
	FVector targetLocation = mTarget->GetActorLocation();
	FVector targetRotation = mTarget->GetActorRotation().Vector();
	FVector frontOfTargetLocation = targetLocation + (targetRotation * 150);
	mOwner->SetActorLocation(frontOfTargetLocation);
	const FDamageEvent damageEvent;

	mTarget->TakeDamage(mDamage, damageEvent, mOwner->GetController(), mOwner);
}


