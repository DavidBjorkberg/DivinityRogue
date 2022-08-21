// Fill out your copyright notice in the Description page of Project Settings.


#include "DRUseAbilityNotify.h"

void UDRUseAbilityNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(MeshComp->GetName().Contains("Debug")) return;
	check(mAbility != nullptr)
	check(mUser != nullptr)
	check(mTarget != nullptr)
	mAbility->Use(mUser, mTarget);
}

void UDRUseAbilityNotify::SetParameters(UDRAbility* ability, ADRCharacter* user, ADRCharacter* target)
{
	mAbility = ability;
	mUser = user;
	mTarget = target;
}
