// Fill out your copyright notice in the Description page of Project Settings.


#include "DRHealthComponent.h"

#include "DRGameplayStatics.h"


void UDRHealthComponent::ModifyHealth(int difference)
{
	UDRGameplayStatics::GetHUD(GetWorld())->SpawnFloatingDamageText(GetOwner(),FMath::Abs(difference), difference > 0);
	mCurrentHealth = FMath::Clamp(mCurrentHealth + difference, 0, mMaxHealth);
	mCharTemplate->CurrentHealth = mCurrentHealth;
	mOnHealthChanged.Broadcast(mCurrentHealth);
	if(mCurrentHealth == 0)
	{
		mOnDied.Broadcast();
	}
}

void UDRHealthComponent::ApplyTemplate(UDRCharacterTemplate* charTemplate)
{
	mCharTemplate = charTemplate;
	mMaxHealth = charTemplate->MaxHealth;
	mCurrentHealth = charTemplate->CurrentHealth;
}
