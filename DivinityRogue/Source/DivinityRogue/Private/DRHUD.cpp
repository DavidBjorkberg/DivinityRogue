// Fill out your copyright notice in the Description page of Project Settings.


#include "DRHUD.h"

void ADRHUD::StartTargeting(ADRCharacter* character, ADRAbility* ability)
{
	mTargetingAbility = ability;
	mCharacterUsingAbility = character;
}

void ADRHUD::StopTargeting()
{
	mTargetingAbility = nullptr;
	mCharacterUsingAbility = nullptr;
}

void ADRHUD::DrawHUD()
{
	Super::DrawHUD();
	if (mTargetingAbility == nullptr) return;

	DrawCircle(GetWorld(), mCharacterUsingAbility->GetActorLocation() + FVector::UpVector * 0.1f, FVector::RightVector, FVector::ForwardVector,
	           FColor::Orange, mTargetingAbility->GetRange(), 3000, false,-1,0,10);
}
