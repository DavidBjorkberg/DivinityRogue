// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_SingleTarget.h"

#include "DREnemyCharacter.h"
#include "DRGameplayStatics.h"
#include "DRPlayerCharacter.h"

void UDRAbility_SingleTarget::OnLeftMouseDown()
{
	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		ADRCharacter* characterUnderCursor = mPlayerController->GetCharacterUnderCursor();
		if (characterUnderCursor != nullptr && IsValidTarget(characterUnderCursor) && IsInRange(characterUnderCursor))
		{
			mTarget = characterUnderCursor;
			mGameMode->GetCharacterInPlay()->PlayAttackAnimation(this);
		}
		mGameMode->SetSelectedAbility(-1);
		mGameMode->SetGameplayState(EGameplayState::PlanningPath);
	}
}

bool UDRAbility_SingleTarget::TrySetRandomTargets()
{
	mTarget = nullptr;
	
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
	ADRCharacter* closestEnemyUnit;
	float closestDistance;
	UDRGameplayStatics::GetClosestDRCharacterInList(mOwner, allEnemyUnits, closestEnemyUnit, closestDistance);
	if(IsInRange(closestEnemyUnit))
	{
		mTarget = closestEnemyUnit;
	}
	return CanCast();
}

bool UDRAbility_SingleTarget::CanCast()
{
	return mTarget != nullptr && CanAffordCast();
}

void UDRAbility_SingleTarget::ClearSelection()
{
	mTarget = nullptr;
}
