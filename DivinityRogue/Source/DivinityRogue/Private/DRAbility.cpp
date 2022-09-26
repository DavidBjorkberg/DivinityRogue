// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility.h"

#include "DRCharacter.h"
#include "DRGameMode.h"
#include "DRGameplayStatics.h"
#include "DRPlayerController.h"

UDRAbility::UDRAbility()
{
}

void UDRAbility::PostInitProperties()
{
	UObject::PostInitProperties();
	if (!GetWorld()) return;

	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mPlayerController = Cast<ADRPlayerController>(GetWorld()->GetFirstPlayerController());
	mGameMode->mOnSelectedAbilityChanged.AddDynamic(this, &UDRAbility::OnSelectedAbilityChanged);
}

void UDRAbility::Use()
{
	mGameMode->GetCharacterInPlay()->ModifyEnergy(-mAbilityInfo.mActionPointCost);
}

UWorld* UDRAbility::GetWorld() const
{
	// Return pointer to World from object owner, if we don’t work in editor
	if (GIsEditor && !GIsPlayInEditorWorld)
	{
		return nullptr;
	}
	else if (GetOuter())
	{
		return GetOuter()->GetWorld();
	}
	return nullptr;
}

bool UDRAbility::IsInRange(ADRCharacter* target)
{
	float distanceToTarget = UDRGameplayStatics::GetDistanceToEdge2D(mOwner,target);
	return distanceToTarget <= mAbilityInfo.mRange;
}

bool UDRAbility::IsValidTarget(ADRCharacter* target)
{
	switch (mAbilityInfo.mTargetType)
	{
	case TargetType::ENEMY:
		return mOwner->GetTeam() != target->GetTeam();
	case TargetType::ALLY:
		return mOwner->GetTeam() == target->GetTeam() || target->GetTeam() == ETeam::NEUTRAL;
	case TargetType::ANY:
		return true;
	default:
		return false;
	}
}

bool UDRAbility::CanAffordCast()
{
	return mOwner->GetCharacterStats().mCurrentActionPoints >= mAbilityInfo.mActionPointCost;;
}

void UDRAbility::OnSelectedAbilityChanged(UDRAbility* ability)
{
	if (ability == this && !mIsSelected)
	{
		mIsSelected = true;
		ClearSelection();
		mPlayerController->mOnLeftMouseDown.AddDynamic(this, &UDRAbility::OnLeftMouseDown);
	}
	else
	{
		mIsSelected = false;
		mPlayerController->mOnLeftMouseDown.RemoveDynamic(this, &UDRAbility::OnLeftMouseDown);
	}
}
