// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Haste.h"

void UDRAbility_Haste::Use()
{
	Super::Use();
	mTarget->ModifyEnergy(mEnergyIncrease);
}
