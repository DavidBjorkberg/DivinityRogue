// Fill out your copyright notice in the Description page of Project Settings.


#include "DRCursor.h"

#include "DRPlayerController.h"

void UDRCursor::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (!mIsInitialized)
	{
		if (ADRPlayerController* pc = GetWorld()->GetFirstPlayerController<ADRPlayerController>())
		{
			pc->mCurrentCursorWidget = this;
			mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
			mPlayerController = GetWorld()->GetFirstPlayerController<ADRPlayerController>();
			mRoundSystem = GetWorld()->GetSubsystem<UDRRoundSystem>();
			mIsInitialized = true;
		}
	}
	else
	{
		Clear();
		if (mRoundSystem->IsPlayersTurn() &&
			mGameMode->IsInGameplayState(EGameplayState::PlanningPath) &&
			mPlayerController->GetMouseHoverState() != HoverUI)
		{
			ShowCostText();
			if (mPlayerController->GetMouseHoverState() != Enemy &&
				mPlayerController->GetMouseHoverState() != EnemyInBasicAttackRange)
			{
				ShowDistanceText();
			}
		}
	}
}

void UDRCursor::Clear()
{
	mCostText->SetVisibility(ESlateVisibility::Collapsed);
	mDistanceText->SetVisibility(ESlateVisibility::Collapsed);
}

void UDRCursor::ShowCostText()
{
	int cost;
	if (mPlayerController->GetMouseHoverState() == Enemy || mPlayerController->GetMouseHoverState() ==
		EnemyInBasicAttackRange)
	{
		UDRAbility_BasicAttack* basicAttack = mRoundSystem->GetCharacterInPlay()->GetAbilityComponent()->
		                                                    GetBasicAttack();
		cost = basicAttack->GetAbilityInfo().mActionPointCost;
	}
	else
	{
		cost = mRoundSystem->GetCharacterInPlay()->GetDRMovementComponent()->GetEnergyCostToMouse();
	}
	int currentEnergy = mRoundSystem->GetCharacterInPlay()->GetStatsComponent()->GetStats().mCurrentEnergy;
	bool canAfford = currentEnergy >= cost;
	FString costText = "Cost: " + FString::FromInt(cost);

	mCostText->SetColorAndOpacity(canAfford ? FColor::Black : FColor::Red);
	mCostText->SetText(FText::FromString(costText));
	mCostText->SetVisibility(ESlateVisibility::Visible);
}

void UDRCursor::ShowDistanceText()
{
	float pathLength = mRoundSystem->GetCharacterInPlay()->GetDRMovementComponent()->GetPathLengthToMouse();

	float pathLengthInMeters = pathLength / 100.0f;
	FString pathLengthText = FString::SanitizeFloat(pathLengthInMeters);
	int index;
	pathLengthText.FindChar('.', index);
	pathLengthText.RemoveAt(index + 2, pathLengthText.Len());
	mDistanceText->SetText(FText::FromString(pathLengthText + "m"));
	mDistanceText->SetVisibility(ESlateVisibility::Visible);
}

void UDRCursor::UpdateCursor(EMouseHoverState newState)
{
	if (newState == Enemy ||
		newState == EnemyInBasicAttackRange)
	{
		mImage->SetBrushFromTexture(mAttackTexture);
	}
	else
	{
		mImage->SetBrushFromTexture(mDefaultTexture);
	}
}
