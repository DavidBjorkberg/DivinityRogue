// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Slam.h"

#include "DRCharacter.h"
#include "DRGameplayStatics.h"

void UDRAbility_Slam::Use()
{
	Super::Use();
	mTarget->TakeDamage(mDamage, mOwner);
	UDRGameplayStatics::PlaySoundAtLocation(GetWorld(), mOnUsedSound, mOwner->GetActorLocation());
	FVector belowTargetLocation = mTarget->GetOwner()->GetActorLocation() - FVector(0,0,mOwner->GetSimpleCollisionHalfHeight()) ;
	UDRGameplayStatics::SpawnEmitterAtLocation(GetWorld(),mOnUsedParticleEffect,belowTargetLocation);
}
