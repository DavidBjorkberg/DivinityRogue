// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Slam.h"

#include "DRCharacter.h"

void UDRAbility_Slam::Use()
{
	Super::Use();
	mTarget->TakeDamage(mDamage, mOwner);
}
