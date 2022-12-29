// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Whirlwind.h"

#include "DRGameplayStatics.h"

void UDRAbility_Whirlwind::Use()
{
	Super::Use();
	TArray<UDRAbilityTargetComponent*> abilityTargetsInRange = UDRGameplayStatics::GetAllAbilityTargetsInRadius(
		mWorld,
		mOwner->GetActorLocation(),
		mAbilityInfo.mRange);
	
	for (UDRAbilityTargetComponent* AbilityTargetInRange : abilityTargetsInRange)
	{
		if (IsTargetCorrectTeam(AbilityTargetInRange))
		{
			AbilityTargetInRange->TakeDamage(mDamage, mOwner);
		}
	}
	FVector emitterLocation = mOwner->GetActorLocation() - FVector(0,0,mOwner->GetSimpleCollisionHalfHeight());
	UDRGameplayStatics::PlaySoundAtLocation(GetWorld(), mOnUsedSound, mOwner->GetActorLocation());
	UDRGameplayStatics::SpawnEmitterAtLocation(GetWorld(),mOnUsedParticleEffect,emitterLocation);
}
