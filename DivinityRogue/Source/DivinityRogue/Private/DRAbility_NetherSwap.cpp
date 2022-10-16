// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_NetherSwap.h"

#include "DRCharacter.h"

void UDRAbility_NetherSwap::Use()
{
	Super::Use();
	FVector locationA = mTargets[0]->GetActorLocation();
	FVector locationB = mTargets[1]->GetActorLocation();
	mTargets[0]->SetActorLocation(locationB);
	mTargets[1]->SetActorLocation(locationA);
}
