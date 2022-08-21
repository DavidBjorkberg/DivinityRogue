// Fill out your copyright notice in the Description page of Project Settings.


#include "DRFinishAttackNotify.h"

#include "DRCharacter.h"

void UDRFinishAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(MeshComp->GetName().Contains("Debug")) return;
	Cast<ADRCharacter>(MeshComp->GetOwner())->OnFinishedAttack();
}
