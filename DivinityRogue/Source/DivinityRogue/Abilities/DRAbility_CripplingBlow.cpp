// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_CripplingBlow.h"

#include "DRAbility_Slam.h"

#include "DRGameplayStatics.h"

void UDRAbility_CripplingBlow::Use()
{
	Super::Use();
	TArray<UDRAbilityTargetComponent*> targetsAroundTarget = UDRGameplayStatics::GetAllAbilityTargetsInRadius(
		GetWorld(), mTarget->GetOwner()->GetActorLocation(), mRadius);
	for (int i = targetsAroundTarget.Num() - 1; i >= 0; i--)
	{
		if (IsTargetCorrectTeam(targetsAroundTarget[i]))
		{
			targetsAroundTarget[i]->TakeDamage(mDamage, mOwner);
			//TODO: Apply cripple
		}
	}
}

bool UDRAbility_CripplingBlow::AIShouldUse()
{
	return Super::AIShouldUse();
}
