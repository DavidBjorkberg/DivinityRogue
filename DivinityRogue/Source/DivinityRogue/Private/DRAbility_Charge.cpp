// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Charge.h"

#include "DRCharacter.h"

void UDRAbility_Charge::Use()
{
	Super::Use();
	FVector targetLocation = mTarget->GetOwner()->GetActorLocation();
	FVector targetRotation = mTarget->GetOwner()->GetActorRotation().Vector();
	FVector frontOfTargetLocation = targetLocation + (targetRotation * 150);
	mOwner->FindComponentByClass<UDRAbilityTargetComponent>()->TeleportTo(frontOfTargetLocation);
	mTarget->TakeDamage(mDamage, mOwner);
}
