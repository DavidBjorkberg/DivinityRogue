// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_BasicAttack.h"
#include "DRCharacter.h"

void UDRAbility_BasicAttack::Use(ADRCharacter* user, ADRCharacter* target)
{
	Super::Use(user, target);
	FDamageEvent damageEvent;
	target->TakeDamage(mDamage, damageEvent, user->GetController(), user);
}
