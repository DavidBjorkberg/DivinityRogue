// Fill out your copyright notice in the Description page of Project Settings.


#include "DRUnitInfo.h"

#include "Animation/WidgetAnimation.h"
#include "Components/HorizontalBoxSlot.h"

void UDRUnitInfo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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

void UDRUnitInfo::Init(ADRCharacter* character)
{
	mCharacter = character;
	if (character->GetAbilityTargetComponent()->GetTeam() == ETeam::ENEMY)
	{
		mBorder->SetBrushColor(FLinearColor(1, 0, 0, 1));
	}
	mImage->SetBrushFromTexture(character->mCharacterTemplate->Icon);
	character->GetHealthComponent()->mOnHealthChanged.AddDynamic(this, &UDRUnitInfo::OnHealthChange);
	OnHealthChange(character->GetHealthComponent()->GetCurrentHealth());
}

void UDRUnitInfo::OnHealthChange(int newHealth)
{
	UDRHealthComponent* healthComp = mCharacter->GetHealthComponent();
	mHealthbar->UpdateHealthbar(healthComp->GetMaxHealth(), newHealth);
}

void UDRUnitInfo::Highlight()
{
	ForceLayoutPrepass();
	FVector2D defaultSize = GetDesiredSize();
	mSizeBox->SetWidthOverride(defaultSize.X * mHighlightedSize);
	mSizeBox->SetHeightOverride(defaultSize.Y * mHighlightedSize);
	mNameText->SetText(mCharacter->mCharacterTemplate->Name);
}

void UDRUnitInfo::Unhighlight()
{
	mSizeBox->ClearWidthOverride();
	mSizeBox->ClearHeightOverride();
	mNameText->SetText(FText::FromString(""));
}

void UDRUnitInfo::StartSlide(float targetX)
{
	mTargetX = targetX;
	mT = 0;
	mIsSliding = true;
}
