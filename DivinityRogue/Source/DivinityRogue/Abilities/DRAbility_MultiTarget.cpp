// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_MultiTarget.h"

#include "DRGameplayStatics.h"
#include "DRPlayerController.h"

void UDRAbility_MultiTarget::OnLeftMouseDown()
{
	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		UDRAbilityTargetComponent* abilityTargetUnderCursor = mPlayerController->GetAbilityTargetUnderCursor();
		if (IsValidTarget(abilityTargetUnderCursor))
		{
			mTargets.Add(abilityTargetUnderCursor);
			if (mTargets.Num() == mNumberOfTargets)
			{
				mRoundSystem->GetCharacterInPlay()->UseAbility(this);
				DeselectAbility();
			}
		}
		else
		{
			DeselectAbility();
			mGameMode->SetGameplayState(EGameplayState::PlanningPath);
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

	return mTargets.Num() == mNumberOfTargets;
}

void UDRAbility_MultiTarget::ClearSelection()
{
	mTargets.Empty();
}

bool UDRAbility_MultiTarget::IsValidTarget(UDRAbilityTargetComponent* target)
{
	return target != nullptr && IsTargetCorrectTeam(target) && IsInRange(
		target);
}

FVector UDRAbility_MultiTarget::GetTargetLocation()
{
	FVector averageLocation = FVector::Zero();
	for(int i = 0; i < mTargets.Num();i++)
	{
		averageLocation += mTargets[i]->GetOwner()->GetActorLocation();
	}
	averageLocation /= mTargets.Num();
	return averageLocation;
}
