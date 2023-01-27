// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Restoration.h"

#include "DRGameplayStatics.h"

void UDRAbility_Restoration::Use()
{
	Super::Use();
	mTarget->Heal(mHealing);
}

bool UDRAbility_Restoration::AIShouldUse()
{
	return TrySetRandomTargets();
}

bool UDRAbility_Restoration::TrySetRandomTargets()
{
	TArray<UDRAbilityTargetComponent*> targetsInRange = GetAllValidTargetsInRadius(
	mOwner->GetActorLocation(), GetRange(), false);
	if(targetsInRange.Num() == 0)
	{
		return false;
	}
	
	float lowestHealthPercent = 1.0f;
	ADRCharacter* lowestHealthCharacter = nullptr;
	for (int i = targetsInRange.Num() - 1; i >= 0; i--)
	{
		ADRCharacter* character = Cast<ADRCharacter>(targetsInRange[i]->GetOwner());
		int currentHealth = character->GetHealthComponent()->GetCurrentHealth();
		int maxHealth = character->GetHealthComponent()->GetMaxHealth();
		float healthPercent = currentHealth / maxHealth;
		if(healthPercent < lowestHealthPercent)
		{
			lowestHealthPercent = healthPercent;
			lowestHealthCharacter = character;
		}
	}
	
	if(lowestHealthPercent > mTargetMaximumHealthPercent)
	{
		return false;
	}
	
	mTarget = lowestHealthCharacter->GetAbilityTargetComponent();
	return true;
}
