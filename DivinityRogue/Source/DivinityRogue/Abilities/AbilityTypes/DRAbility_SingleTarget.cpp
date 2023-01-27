// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_SingleTarget.h"

#include "DRGameplayStatics.h"
#include "DRPlayerController.h"

void UDRAbility_SingleTarget::OnLeftMouseDown()
{
	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		UDRAbilityTargetComponent* abilityTargetUnderCursor = mPlayerController->GetAbilityTargetUnderCursor();
		if (IsValidTarget(abilityTargetUnderCursor))
		{
			mTarget = abilityTargetUnderCursor;
			mRoundSystem->GetCharacterInPlay()->UseAbility(this);
		}
		else
		{
			mGameMode->SetGameplayState(EGameplayState::PlanningPath);
		}
		DeselectAbility();
	}
}

bool UDRAbility_SingleTarget::TrySetRandomTargets()
{
	mTarget = nullptr;

	TArray<UDRAbilityTargetComponent*> targetsInRange = GetAllValidTargetsInRadius(
	mOwner->GetActorLocation(), GetRange(), true);
	if(targetsInRange.Num() == 0)
	{
		return false;
	}
	UDRGameplayStatics::SortComponentListByDistance(mOwner, targetsInRange);
	mTarget = targetsInRange[0];
	return true;
}

void UDRAbility_SingleTarget::ClearSelection()
{
	mTarget = nullptr;
}

bool UDRAbility_SingleTarget::IsValidTarget(UDRAbilityTargetComponent* target)
{
	return target != nullptr && IsTargetCorrectTeam(target) && IsInRange(target);
}
