// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Battlecry.h"

#include "DRCharacter.h"

void UDRAbility_Battlecry::Use()
{
	Super::Use();
	mOwner->Heal(mHealAmount);
}
