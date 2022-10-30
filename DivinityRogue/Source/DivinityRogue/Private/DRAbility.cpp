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

	mWorld = GetWorld();
	mGameMode = mWorld->GetAuthGameMode<ADRGameMode>();
	mPlayerController = Cast<ADRPlayerController>(GetWorld()->GetFirstPlayerController());
	mGameMode->mOnSelectedAbilityChanged.AddDynamic(this, &UDRAbility::OnSelectedAbilityChanged);
	mGameMode->mOnNewRound.AddDynamic(this, &UDRAbility::OnNewRound);
}

void UDRAbility::Use()
{
	mOwner->ModifyEnergy(-mAbilityInfo.mActionPointCost);
	mRemainingCooldown = mAbilityInfo.mCooldown;
	mOwner->mOnUsedAbility.Broadcast(this);
}

void UDRAbility::OnAbilitySelected()
{
	mIsSelected = true;
	ClearSelection();
	mPlayerController->mOnLeftMouseDown.AddDynamic(this, &UDRAbility::OnLeftMouseDown);
}

void UDRAbility::OnAbilityDeselected()
{
	mIsSelected = false;
	mPlayerController->mOnLeftMouseDown.RemoveDynamic(this, &UDRAbility::OnLeftMouseDown);
}

void UDRAbility::DeselectAbility()
{
	mGameMode->TrySelectAbility(-1);
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
	float distanceToTarget = UDRGameplayStatics::GetDistanceToEdge2D(mOwner->GetActorLocation(), target);
	return distanceToTarget <= mAbilityInfo.mRange;
}

bool UDRAbility::IsInRange(FVector targetLocation)
{
	float distanceToTarget = FVector::Distance(mOwner->GetActorLocation(), targetLocation);
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
	return mOwner->GetStatsComponent()->GetStats().mCurrentActionPoints >= mAbilityInfo.mActionPointCost;;
}

void UDRAbility::OnSelectedAbilityChanged(UDRAbility* ability)
{
	if (ability == this && !mIsSelected)
	{
		OnAbilitySelected();
	}
	else if (mIsSelected)
	{
		OnAbilityDeselected();
	}
}

void UDRAbility::OnNewRound()
{
	if (mRemainingCooldown > 0)
	{
		mRemainingCooldown--;
	}
}
