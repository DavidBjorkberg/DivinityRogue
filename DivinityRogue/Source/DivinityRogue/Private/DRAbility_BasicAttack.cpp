// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_BasicAttack.h"
#include "DRCharacter.h"

bool UDRAbility_BasicAttack::TryUse(ADRCharacter* user,ADRCharacter* target)
{
	if(!IsInRange(user,target)) return false;
	
	FDamageEvent damageEvent;
	target->TakeDamage(mDamage,damageEvent,user->GetController(),user);
	return true;
}
