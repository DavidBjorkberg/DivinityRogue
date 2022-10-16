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
		ADRCharacter* characterUnderCursor = mPlayerController->GetCharacterUnderCursor();
		if (characterUnderCursor == nullptr || !IsValidTarget(characterUnderCursor) || !IsInRange(characterUnderCursor))
		{
			DeselectAbility();
			mGameMode->SetGameplayState(EGameplayState::PlanningPath);
			return;
		}
		
		mTargets.Add(characterUnderCursor);
		if (mTargets.Num() == mNumberOfTargets)
		{
			mGameMode->GetCharacterInPlay()->GetAnimationComponent()->PlayAttackAnimation(this);
			DeselectAbility();
		}
	}
}

bool UDRAbility_MultiTarget::TrySetRandomTargets()
{
	mTargets.Empty();

	TArray<ADRCharacter*> allEnemyUnits;
	if (Cast<ADRPlayerCharacter>(mOwner))
	{
		for (auto enemy : mGameMode->GetAllEnemyUnits())
		{
			allEnemyUnits.Add(enemy);
		}
	}
	else if (Cast<ADREnemyCharacter>(mOwner))
	{
		for (auto enemy : mGameMode->GetAllPlayerUnits())
		{
			allEnemyUnits.Add(enemy);
		}
	}
	UDRGameplayStatics::SortActorListByDistance(mOwner, allEnemyUnits);
	for (auto enemy : allEnemyUnits)
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
