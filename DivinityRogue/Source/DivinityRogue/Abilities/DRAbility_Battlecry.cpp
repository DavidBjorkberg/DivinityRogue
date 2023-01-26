// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Battlecry.h"

#include "DRCharacter.h"
#include "DRGameplayStatics.h"

void UDRAbility_Battlecry::Use()
{
	Super::Use();
	mOwner->Heal(mHealAmount);
	UDRGameplayStatics::PlaySoundAtLocation(GetWorld(), mOnUsedSound, mOwner->GetActorLocation());
	UDRGameplayStatics::SpawnEmitterAtLocation(GetWorld(),mOnUsedParticleEffect,mOwner->GetActorLocation());

}

bool UDRAbility_Battlecry::AIShouldUse()
{
	return Super::AIShouldUse();
}
