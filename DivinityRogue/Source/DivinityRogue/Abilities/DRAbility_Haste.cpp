// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Haste.h"

#include "DRCharacter.h"
#include "DRGameplayStatics.h"

void UDRAbility_Haste::Use()
{
	Super::Use();
	mTarget->ModifyEnergy(mEnergyIncrease);
	UDRGameplayStatics::PlaySoundAtLocation(GetWorld(), mOnUsedSound, mTarget->GetOwner()->GetActorLocation());
	UDRGameplayStatics::SpawnEmitterAtLocation(GetWorld(),mOnUsedParticleEffect,mTarget->GetOwner()->GetActorLocation());

}
