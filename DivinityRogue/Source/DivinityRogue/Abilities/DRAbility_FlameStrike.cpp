// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_FlameStrike.h"

#include "DRCharacter.h"
#include "DRGameplayStatics.h"

void UDRAbility_FlameStrike::Use()
{
	Super::Use();
	UDRGameplayStatics::PlaySoundAtLocation(GetWorld(), mOnUsedSound, mTargetLocation);
	UDRGameplayStatics::SpawnEmitterAtLocation(GetWorld(),mOnUsedParticleEffect,mTargetLocation);
	for (auto target : mTargets)
	{
		target->TakeDamage(mDamage, mOwner);
	}
}
