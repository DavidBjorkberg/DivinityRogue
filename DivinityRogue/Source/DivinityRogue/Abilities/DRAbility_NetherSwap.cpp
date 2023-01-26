// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_NetherSwap.h"

#include "DRCharacter.h"
#include "DRGameplayStatics.h"

void UDRAbility_NetherSwap::Use()
{
	Super::Use();
	FVector locationA = mTargets[0]->GetOwner()->GetActorLocation();
	FVector locationB = mTargets[1]->GetOwner()->GetActorLocation();
	mTargets[0]->TeleportTo(locationB);
	mTargets[1]->TeleportTo(locationA);
	UDRGameplayStatics::PlaySoundAtLocation(GetWorld(), mOnUsedSound, locationA);
	UDRGameplayStatics::SpawnEmitterAtLocation(GetWorld(),mOnUsedParticleEffect,locationB);
	UDRGameplayStatics::SpawnEmitterAtLocation(GetWorld(),mOnUsedParticleEffect,locationA);

}

bool UDRAbility_NetherSwap::AIShouldUse()
{
	return Super::AIShouldUse();
}
