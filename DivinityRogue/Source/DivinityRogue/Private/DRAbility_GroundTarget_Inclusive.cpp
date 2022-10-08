// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_GroundTarget_Inclusive.h"

#include "DRGameplayStatics.h"

void UDRAbility_GroundTarget_Inclusive::OnLeftMouseDown()
{
	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		FHitResult groundUnderCursorHitResult;
		UDRGameplayStatics::GetGroundHitResultUnderCursor(GetWorld(), groundUnderCursorHitResult, false);
		if (IsOnValidArea())
		{
			mTargetLocation = groundUnderCursorHitResult.Location;
			mTargets = UDRGameplayStatics::GetAllCharactersInRadius(GetWorld(), groundUnderCursorHitResult.Location,
			                                                        mRadius);
			for(int i = mTargets.Num()-1; i >= 0; i--)
			{
				if(!IsValidTarget(mTargets[i]))
				{
					mTargets.RemoveAt(i);
				}
			}
			mGameMode->GetCharacterInPlay()->PlayAttackAnimation(this);
		}
			DeselectAbility();
	}
}
