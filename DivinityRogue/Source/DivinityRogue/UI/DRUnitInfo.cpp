// Fill out your copyright notice in the Description page of Project Settings.


#include "DRUnitInfo.h"

void UDRUnitInfo::Init(ADRCharacter* character)
{
	mCharacter = character;
	if(character->GetAbilityTargetComponent()->GetTeam() == ETeam::ENEMY)
	{
		mBorder->SetBrushTintColor(FSlateColor(FLinearColor(1,0,0,1)));
	}
	mImage->SetBrushFromTexture(character->mCharacterTemplate->Icon);
	character->GetHealthComponent()->mOnHealthChanged.AddDynamic(this, &UDRUnitInfo::OnHealthChange);
	OnHealthChange(character->GetHealthComponent()->GetCurrentHealth());
}

void UDRUnitInfo::OnHealthChange(int newHealth)
{
	UDRHealthComponent* healthComp = mCharacter->GetHealthComponent();
	mHealthbar->UpdateHealthbar(healthComp->GetMaxHealth(),newHealth);
}
