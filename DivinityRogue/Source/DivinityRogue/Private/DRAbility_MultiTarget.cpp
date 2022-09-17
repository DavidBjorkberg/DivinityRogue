// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_MultiTarget.h"

#include "DREnemyCharacter.h"
#include "DRGameplayStatics.h"
#include "DRPlayerCharacter.h"

void UDRAbility_MultiTarget::OnLeftMouseDown()
{
	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		ADRCharacter* characterUnderCursor = mPlayerController->GetCharacterUnderCursor();
		if (characterUnderCursor != nullptr && IsValidTarget(characterUnderCursor) && IsInRange(characterUnderCursor))
		{
			mTargetedCharacters.Add(characterUnderCursor);
			if (mTargetedCharacters.Num() == mNumberOfTargets)
			{
				mGameMode->GetCharacterInPlay()->PlayAttackAnimation(this);
			}
		}
		else
		{
			mGameMode->SetSelectedAbility(-1);
			mGameMode->SetGameplayState(EGameplayState::PlanningPath);
		}
	}
}

bool UDRAbility_MultiTarget::TrySetRandomTargets()
{
	mTargetedCharacters.Empty();

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
			mTargetedCharacters.Add(enemy);
		}
	}

	return CanCast();
}

bool UDRAbility_MultiTarget::CanCast()
{
	return mTargetedCharacters.Num() > 0 && CanAffordCast();
}

void UDRAbility_MultiTarget::ClearSelection()
{
	mTargetedCharacters.Empty();
}
