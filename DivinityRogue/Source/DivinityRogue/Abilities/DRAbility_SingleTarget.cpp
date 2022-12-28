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

	TArray<UDRAbilityTargetComponent*> allEnemyTargets;
	TArray<UDRAbilityTargetComponent*> allAbilityTargets;
	UDRGameplayStatics::FindAllComponents<UDRAbilityTargetComponent>(GetWorld(), allAbilityTargets);
	UDRAbilityTargetComponent* ownerAbilityTarget = mOwner->FindComponentByClass<UDRAbilityTargetComponent>();
	for (auto abilityTarget : allAbilityTargets)
	{
		if (abilityTarget->GetTeam() != ownerAbilityTarget->GetTeam() && abilityTarget->GetTeam() != ETeam::NEUTRAL)
		{
			allEnemyTargets.Add(abilityTarget);
		}
	}
	UDRGameplayStatics::SortComponentListByDistance(mOwner, allEnemyTargets);
	if (IsValidTarget(allEnemyTargets[0]))
	{
		mTarget = allEnemyTargets[0];
	}
	return mTarget != nullptr;
}

void UDRAbility_SingleTarget::ClearSelection()
{
	mTarget = nullptr;
}

bool UDRAbility_SingleTarget::IsValidTarget(UDRAbilityTargetComponent* target)
{
	return target != nullptr && IsTargetCorrectTeam(target) && IsInRange(target);
}
