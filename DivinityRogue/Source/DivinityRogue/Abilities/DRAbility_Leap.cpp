// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Leap.h"

#include "DRCharacter.h"
#include "DRGameplayStatics.h"

void UDRAbility_Leap::Use()
{
	Super::Use();
	FVector startLocation = mOwner->GetActorLocation();
	mOwner->FindComponentByClass<UDRAbilityTargetComponent>()->TeleportTo(mTargetLocation);
	UDRGameplayStatics::PlaySoundAtLocation(GetWorld(), mOnUsedSound, startLocation);
	UDRGameplayStatics::SpawnEmitterAtLocation(GetWorld(),mOnUsedParticleEffect,startLocation);

}
