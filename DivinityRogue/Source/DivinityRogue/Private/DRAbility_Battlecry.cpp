// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Battlecry.h"

void UDRAbility_Battlecry::Use()
{
	Super::Use();
	mOwner->Heal(mHealAmount);
}
