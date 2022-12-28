// Fill out your copyright notice in the Description page of Project Settings.


#include "DRUseAbilityNotify.h"

void UDRUseAbilityNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(MeshComp->GetName().Contains("Debug") || MeshComp->GetName().Contains("Editor")) return;
	mAbility->Use();
}

void UDRUseAbilityNotify::SetParameters(UDRAbility* ability)
{
	mAbility = ability;
}
