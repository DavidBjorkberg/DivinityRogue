// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_GroundTarget_Exclusive.h"

#include "DRGameplayStatics.h"

void UDRAbility_GroundTarget_Exclusive::OnLeftMouseDown()
{
	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		FHitResult groundUnderCursorHitResult;
		if (UDRGameplayStatics::GetGroundHitResultUnderCursor(GetWorld(), groundUnderCursorHitResult, true) && IsInRange(groundUnderCursorHitResult.Location))
		{
			mTargetLocation = groundUnderCursorHitResult.Location;
			mGameMode->GetCharacterInPlay()->PlayAttackAnimation(this);
		}
		mGameMode->SetSelectedAbility(-1);
		mGameMode->SetGameplayState(EGameplayState::PlanningPath);
	}
}

void UDRAbility_GroundTarget_Exclusive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (mIsSelected)
	{
		FHitResult groundUnderCursorHitResult;
		if (!UDRGameplayStatics::GetGroundHitResultUnderCursor(mWorld, groundUnderCursorHitResult, true) || !IsInRange(groundUnderCursorHitResult.Location))
		{
			SetDecalMaterial(mInvalidDecalMaterial);
		}
		else
		{
			SetDecalMaterial(mDecalMaterial);
		}
	}
}
