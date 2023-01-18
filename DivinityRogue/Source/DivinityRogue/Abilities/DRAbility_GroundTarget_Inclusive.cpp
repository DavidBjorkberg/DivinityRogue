// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_GroundTarget_Inclusive.h"

#include "DRGameplayStatics.h"

void UDRAbility_GroundTarget_Inclusive::OnLeftMouseDown()
{
	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		FHitResult groundUnderCursorHitResult;
		UDRGameplayStatics::GetGroundHitResultUnderCursor(GetWorld(), groundUnderCursorHitResult, false);
		if (IsTargetLocationInRange() && !IsTargetLocationOnWall())
		{
			mTargetLocation = groundUnderCursorHitResult.Location;
			mTargets = UDRGameplayStatics::GetAllAbilityTargetsInRadius(GetWorld(), groundUnderCursorHitResult.Location,
			                                                        mRadius);
			for (int i = mTargets.Num() - 1; i >= 0; i--)
			{
				if (!IsValidTarget(mTargets[i]))
				{
					mTargets.RemoveAt(i);
				}
			}
			mRoundSystem->GetCharacterInPlay()->UseAbility(this);
		}
		else
		{
			mGameMode->SetGameplayState(EGameplayState::PlanningPath);
		}
		DeselectAbility();
	}
}
