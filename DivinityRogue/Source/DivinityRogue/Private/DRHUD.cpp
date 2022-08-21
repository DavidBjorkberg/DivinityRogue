// Fill out your copyright notice in the Description page of Project Settings.


#include "DRHUD.h"

#include "DRCharacter.h"

void ADRHUD::BeginPlay()
{
	Super::BeginPlay();
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mGameMode->mOnGameplayStateChanged.AddDynamic(this, &ADRHUD::OnGameplayStateChanged);
}

void ADRHUD::DrawHUD()
{
	Super::DrawHUD();
	if (!mGameMode->IsPlayersTurn()) return;

	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		ADRCharacter* characterUsingAbility = mGameMode->GetCharacterInPlay();
		DrawCircle(GetWorld(), characterUsingAbility->GetActorLocation() + FVector::UpVector * 0.1f,
		           FVector::RightVector,
		           FVector::ForwardVector,
		           FColor::Orange, mGameMode->mSelectedAbility->GetRange(), 3000, false, -1, 0, 10);
	}
}


void ADRHUD::StartTargeting()
{
	mIsTargeting = true;
}

void ADRHUD::StopTargeting()
{
	mIsTargeting = false;
}

void ADRHUD::OnGameplayStateChanged(EGameplayState oldState, EGameplayState newState)
{
	if (newState == EGameplayState::SelectingTarget)
	{
		StartTargeting();
	}
	else if (oldState == EGameplayState::SelectingTarget)
	{
		StopTargeting();
	}
}
