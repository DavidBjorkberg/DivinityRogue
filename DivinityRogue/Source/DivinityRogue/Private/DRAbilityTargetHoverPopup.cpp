// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbilityTargetHoverPopup.h"

void UDRAbilityTargetHoverPopup::Show(UDRAbilityTargetComponent* target)
{
	if (!mTarget)
	{
		Hide();
	}
	mTarget = target;

	if (mTarget)
	{
		mTargetHealthComponent = mTarget->GetOwner()->FindComponentByClass<UDRHealthComponent>();
		if (mTargetHealthComponent)
		{
			mHealthBar->SetVisibility(ESlateVisibility::Visible);
			mTargetHealthComponent->mOnHealthChanged.AddDynamic(this, &UDRAbilityTargetHoverPopup::OnHealthChanged);
			mHealthBar->UpdateHealthbar(mTargetHealthComponent->GetMaxHealth(),
			                            mTargetHealthComponent->GetCurrentHealth());
		}
		else
		{
			mHealthBar->SetVisibility(ESlateVisibility::Collapsed);
		}
		mNameText->SetText(target->GetName());
		SetVisibility(ESlateVisibility::Visible);
	}
}

void UDRAbilityTargetHoverPopup::Hide()
{
	if (mTargetHealthComponent)
	{
		mTargetHealthComponent->mOnHealthChanged.RemoveDynamic(this, &UDRAbilityTargetHoverPopup::OnHealthChanged);
	}
	SetVisibility(ESlateVisibility::Hidden);
	mTarget = nullptr;
	mTargetHealthComponent = nullptr;
}

void UDRAbilityTargetHoverPopup::OnHealthChanged(int newHealth)
{
	mHealthBar->UpdateHealthbar(mTargetHealthComponent->GetMaxHealth(), mTargetHealthComponent->GetCurrentHealth());
}
