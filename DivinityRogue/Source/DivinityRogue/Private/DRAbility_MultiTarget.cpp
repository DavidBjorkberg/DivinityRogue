// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_MultiTarget.h"

#include "DREnemyCharacter.h"
#include "DRGameplayStatics.h"
#include "DRPlayerCharacter.h"
#include "DRPlayerController.h"

void UDRAbility_MultiTarget::OnLeftMouseDown()
{
	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		UDRAbilityTargetComponent* abilityTargetUnderCursor = mPlayerController->GetAbilityTargetUnderCursor();
		if (abilityTargetUnderCursor == nullptr || !IsValidTarget(abilityTargetUnderCursor) || !IsInRange(
			abilityTargetUnderCursor))
		{
			DeselectAbility();
			mGameMode->SetGameplayState(EGameplayState::PlanningPath);
			return;
		}

		mTargets.Add(abilityTargetUnderCursor);
		if (mTargets.Num() == mNumberOfTargets)
		{
			mGameMode->GetCharacterInPlay()->UseAbility(this);
			DeselectAbility();
		}
	}
}

bool UDRAbility_MultiTarget::TrySetRandomTargets()
{
	mTargets.Empty();

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
	for (auto enemy : allEnemyTargets)
	{
		if (IsInRange(enemy))
		{
			mTargets.Add(enemy);
		}
	}

	return CanCast();
}

bool UDRAbility_MultiTarget::CanCast()
{
	return mTargets.Num() > 0 && CanAffordCast();
}

void UDRAbility_MultiTarget::ClearSelection()
{
	mTargets.Empty();
}
