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
	mRoundSystem = mWorld->GetSubsystem<UDRRoundSystem>();
	mPlayerController = Cast<ADRPlayerController>(GetWorld()->GetFirstPlayerController());
	mGameMode->mOnSelectedAbilityChanged.AddDynamic(this, &UDRAbility::OnSelectedAbilityChanged);
	mRoundSystem->mOnNewRound.AddDynamic(this, &UDRAbility::OnNewRound);
}

void UDRAbility::Use()
{
	mOwner->FindComponentByClass<UDRAbilityTargetComponent>()->ModifyEnergy(-mAbilityInfo.mActionPointCost);
	mRemainingCooldown = mAbilityInfo.mCooldown;
	mOwner->mOnUsedAbility.Broadcast(this);
}

void UDRAbility::OnAbilitySelected()
{
	mOwner->ShowRangeIndicator(mAbilityInfo.mRange);
	mIsSelected = true;
	ClearSelection();
	mPlayerController->mOnLeftMouseDown.AddDynamic(this, &UDRAbility::OnLeftMouseDown);
}

void UDRAbility::OnAbilityDeselected()
{
	mOwner->HideRangeIndicator();
	mIsSelected = false;
	mPlayerController->mOnLeftMouseDown.RemoveDynamic(this, &UDRAbility::OnLeftMouseDown);
}

bool UDRAbility::IsValidTarget(UDRAbilityTargetComponent* target)
{
	return target != nullptr;
}

void UDRAbility::DeselectAbility()
{
	mGameMode->TrySelectAbility(nullptr);
}

FVector UDRAbility::GetTargetLocation()
{
	return FVector::Zero();
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

bool UDRAbility::IsInRange(UDRAbilityTargetComponent* target)
{
	float distanceToTarget = UDRGameplayStatics::GetDistanceToEdge2D(mOwner->GetActorLocation(), target);
	return distanceToTarget <= mAbilityInfo.mRange;
}

bool UDRAbility::IsInRange(FVector targetLocation)
{
	float distanceToTarget = FVector::Dist2D(mOwner->GetActorLocation(), targetLocation);
	return distanceToTarget <= mAbilityInfo.mRange;
}

bool UDRAbility::IsTargetCorrectTeam(UDRAbilityTargetComponent* targetSelectable)
{
	ETeam ownerTeam = mOwner->FindComponentByClass<UDRAbilityTargetComponent>()->GetTeam();
	ETeam targetTeam = targetSelectable->GetTeam();
	switch (mAbilityInfo.mTargetType)
	{
	case TargetType::ENEMY:
		return ownerTeam != targetTeam;
	case TargetType::ALLY:
		return ownerTeam == targetTeam || targetTeam == ETeam::NEUTRAL;
	case TargetType::ANY:
		return true;
	default:
		return false;
	}
}

bool UDRAbility::CanAffordCast()
{
	return mOwner->GetStatsComponent()->GetStats().mCurrentEnergy >= mAbilityInfo.mActionPointCost;;
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
