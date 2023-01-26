// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Charge.h"

#include "DRCharacter.h"
#include "DRGameplayStatics.h"

void UDRAbility_Charge::Use()
{
	Super::Use();
	FVector targetLocation = mTarget->GetOwner()->GetActorLocation();
	FVector targetRotation = mTarget->GetOwner()->GetActorRotation().Vector();
	FVector frontOfTargetLocation = targetLocation + (targetRotation * 150) - FVector(0,0,mOwner->GetSimpleCollisionHalfHeight()) ;
	mOwner->FindComponentByClass<UDRAbilityTargetComponent>()->TeleportTo(frontOfTargetLocation);
	mTarget->TakeDamage(mDamage, mOwner);
	UDRGameplayStatics::SpawnEmitterAtLocation(GetWorld(),mOnUsedParticleEffect,frontOfTargetLocation);
}

bool UDRAbility_Charge::AIShouldUse()
{
	if(TrySetRandomTargets())
	{
		FVector targetLocation = mTarget->GetOwner()->GetActorLocation();
		FVector startLocation = mOwner->GetActorLocation();
		return FVector::Dist2D(startLocation,targetLocation) >= mMinimumDistance;
	}
	return false;
}
