// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_GroundTarget_Exclusive.h"

#include "DRGameplayStatics.h"

void UDRAbility_GroundTarget_Exclusive::OnLeftMouseDown()
{
	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		FHitResult groundUnderCursorHitResult;
		if (IsOnValidArea())
		{
			mTargetLocation = groundUnderCursorHitResult.Location;
			mGameMode->GetCharacterInPlay()->UseAbility(this);
		}
		else
		{
			mGameMode->SetGameplayState(EGameplayState::PlanningPath);
		}
		DeselectAbility();
	}
}

bool UDRAbility_GroundTarget_Exclusive::IsOnValidArea()
{
	FHitResult groundUnderCursorHitResult;
	return UDRGameplayStatics::GetGroundHitResultUnderCursor(GetWorld(), groundUnderCursorHitResult, true) &&
		IsInRange(groundUnderCursorHitResult.Location) &&
		UDRGameplayStatics::GetAllAbilityTargetsInRadius(mWorld, groundUnderCursorHitResult.Location, mRadius).Num() ==
		0;
}
