// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_NoTarget.h"

#include "DRCharacter.h"
#include "DRGameMode.h"

bool UDRAbility_NoTarget::TrySetRandomTargets()
{
	return true;
}

void UDRAbility_NoTarget::ClearSelection()
{
}

void UDRAbility_NoTarget::OnLeftMouseDown()
{
	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		mRoundSystem->GetCharacterInPlay()->UseAbility(this);
		DeselectAbility();
	}
}
