// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Whirlwind.h"

#include "DRGameplayStatics.h"

void UDRAbility_Whirlwind::Use()
{
	Super::Use();
	TArray<ADRCharacter*> charactersInRange = UDRGameplayStatics::GetAllCharactersInRadius(mWorld, mOwner->GetActorLocation(), mAbilityInfo.mRange);
	for (ADRCharacter* characterInRange : charactersInRange)
	{
		if(IsValidTarget(characterInRange))
		{
			const FDamageEvent damageEvent;
			characterInRange->TakeDamage(mDamage, damageEvent, mOwner->GetController(), mOwner);
		}
	}
}
