// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_NoTarget_AOE.h"

#include "DRGameplayStatics.h"

bool UDRAbility_NoTarget_AOE::TrySetRandomTargets()
{
	mTargets = GetAllValidTargetsInRadius(mOwner->GetActorLocation(),GetRange(),false);
	return true;
}
