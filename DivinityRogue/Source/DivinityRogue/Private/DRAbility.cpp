// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility.h"

#include "DRCharacter.h"
#include "DRGameMode.h"
#include "DRPlayerController.h"

UDRAbility::UDRAbility()
{
}

void UDRAbility::PostInitProperties()
{
	UObject::PostInitProperties();
	if(!GetWorld()) return;

	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mPlayerController = Cast<ADRPlayerController>(GetWorld()->GetFirstPlayerController());
	mGameMode->mOnSelectedAbilityChanged.AddDynamic(this,&UDRAbility::OnSelectedAbilityChanged);
}

void UDRAbility::Use(ADRCharacter* user, ADRCharacter* target)
{
	user->ModifyEnergy(-mActionPointCost);
}

bool UDRAbility::CanCast(ADRCharacter* user, ADRCharacter* target)
{
	return IsInRange(user, target) &&
		IsValidTarget(user, target) &&
		user->GetCharacterStats().mCurrentActionPoints >= mActionPointCost;
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

bool UDRAbility::IsInRange(ADRCharacter* user, ADRCharacter* target)
{
	float distanceToTarget = FVector::Dist2D(user->GetActorLocation(), target->GetActorLocation());
	return distanceToTarget <= mRange;
}

bool UDRAbility::IsValidTarget(ADRCharacter* user, ADRCharacter* target)
{
	switch (mTargetType)
	{
	case TargetType::ENEMY:
		return user->GetTeam() != target->GetTeam();
		break;
	case TargetType::ALLY:
		return user->GetTeam() == target->GetTeam() || target->GetTeam() == ETeam::NEUTRAL;
		break;
	case TargetType::ANY:
		return true;
		break;
	default:
		return false;
	}
}

void UDRAbility::OnLeftMouseDown()
{
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mPlayerController = Cast<ADRPlayerController>(GetWorld()->GetFirstPlayerController());
	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		ADRCharacter* characterUnderCursor = mPlayerController->GetCharacterUnderCursor();
		if (characterUnderCursor != nullptr)
		{
			mGameMode->GetCharacterInPlay()->TryUseAbility(mGameMode->GetSelectedAbility(), characterUnderCursor);
		}
		mGameMode->SetSelectedAbility(-1);
		mGameMode->SetGameplayState(EGameplayState::PlanningPath);
	}
}

void UDRAbility::OnSelectedAbilityChanged(UDRAbility* ability)
{
	if(ability == this)
	{
		mPlayerController->mOnLeftMouseDown.AddDynamic(this,&UDRAbility::OnLeftMouseDown);
	}
	else
	{
		mPlayerController->mOnLeftMouseDown.RemoveDynamic(this,&UDRAbility::OnLeftMouseDown);
	}
}
