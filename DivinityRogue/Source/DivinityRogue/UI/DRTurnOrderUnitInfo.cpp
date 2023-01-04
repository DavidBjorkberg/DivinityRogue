// Fill out your copyright notice in the Description page of Project Settings.


#include "DRTurnOrderUnitInfo.h"

#include "Animation/WidgetAnimation.h"
#include "Components/HorizontalBoxSlot.h"

void UDRTurnOrderUnitInfo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (mIsSliding)
	{
		mT = FMath::Clamp(mT + (InDeltaTime / mSlideDuration), 0.0f,1.0f );
		float x = FMath::Lerp(0, mTargetX, mT);
		SetRenderTranslation(FVector2D(x, 0));
		if (mT >= 1)
		{
			mIsSliding = false;
		}
	}
}

void UDRTurnOrderUnitInfo::Init(ADRCharacter* character)
{
	mCharacter = character;
	if (character->GetAbilityTargetComponent()->GetTeam() == ETeam::ENEMY)
	{
		mBorder->SetBrushColor(FLinearColor(1, 0, 0, 1));
	}
	mImage->SetBrushFromTexture(character->mCharacterTemplate->Icon);
	character->GetHealthComponent()->mOnHealthChanged.AddDynamic(this, &UDRTurnOrderUnitInfo::OnHealthChange);
	OnHealthChange(character->GetHealthComponent()->GetCurrentHealth());
}

void UDRTurnOrderUnitInfo::OnHealthChange(int newHealth)
{
	UDRHealthComponent* healthComp = mCharacter->GetHealthComponent();
	mHealthbar->UpdateHealthbar(healthComp->GetMaxHealth(), newHealth);
}

void UDRTurnOrderUnitInfo::Highlight()
{
	ForceLayoutPrepass();
	FVector2D defaultSize = GetDesiredSize();
	mSizeBox->SetWidthOverride(defaultSize.X * mHighlightedSize);
	mSizeBox->SetHeightOverride(defaultSize.Y * mHighlightedSize);
	mNameText->SetText(mCharacter->mCharacterTemplate->Name);
}

void UDRTurnOrderUnitInfo::Unhighlight()
{
	mSizeBox->ClearWidthOverride();
	mSizeBox->ClearHeightOverride();
	mNameText->SetText(FText::FromString(""));
}

void UDRTurnOrderUnitInfo::StartSlide(float targetX)
{
	mTargetX = targetX;
	mT = 0;
	mIsSliding = true;
}
