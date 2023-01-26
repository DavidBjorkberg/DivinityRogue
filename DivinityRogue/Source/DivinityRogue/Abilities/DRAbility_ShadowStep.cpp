// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_ShadowStep.h"

#include "DRCharacter.h"
#include "DRGameplayStatics.h"

void UDRAbility_ShadowStep::Use()
{
	Super::Use();
	FVector startLocation = mOwner->GetActorLocation();
	FVector targetLocation = mTarget->GetOwner()->GetActorLocation();
	FVector targetRotation = mTarget->GetOwner()->GetActorRotation().Vector();
	FVector behindTargetLocation = targetLocation - (targetRotation * 150);
	mOwner->FindComponentByClass<UDRAbilityTargetComponent>()->TeleportTo(behindTargetLocation);
	mTarget->TakeDamage(mDamage, mOwner);
	UDRGameplayStatics::PlaySoundAtLocation(GetWorld(), mOnUsedSound, behindTargetLocation);
	UDRGameplayStatics::SpawnEmitterAtLocation(GetWorld(),mOnUsedParticleEffect,startLocation);
	UDRGameplayStatics::SpawnEmitterAtLocation(GetWorld(),mOnUsedParticleEffect,behindTargetLocation);
}

bool UDRAbility_ShadowStep::AIShouldUse()
{
	return Super::AIShouldUse();
}
