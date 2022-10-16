// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Leap.h"

#include "DRCharacter.h"

void UDRAbility_Leap::Use()
{
	Super::Use();
	mOwner->SetActorLocation(mTargetLocation);
}
