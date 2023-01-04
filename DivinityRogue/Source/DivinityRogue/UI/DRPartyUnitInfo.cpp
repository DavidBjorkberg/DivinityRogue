// Fill out your copyright notice in the Description page of Project Settings.


#include "DRPartyUnitInfo.h"

void UDRPartyUnitInfo::Init(ADRCharacter* character)
{
	mCharacter = character;
	mImage->SetBrushFromTexture(character->mCharacterTemplate->Icon);
	character->GetHealthComponent()->mOnHealthChanged.AddDynamic(this, &UDRPartyUnitInfo::OnHealthChange);
	OnHealthChange(character->GetHealthComponent()->GetCurrentHealth());

}

void UDRPartyUnitInfo::OnHealthChange(int newHealth)
{
	UDRHealthComponent* healthComp = mCharacter->GetHealthComponent();
	mHealthbar->UpdateHealthbar(healthComp->GetMaxHealth(), newHealth);
}
