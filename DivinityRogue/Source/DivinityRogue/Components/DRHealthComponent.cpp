// Fill out your copyright notice in the Description page of Project Settings.


#include "DRHealthComponent.h"

#include "DRGameplayStatics.h"

// Sets default values for this component's properties
UDRHealthComponent::UDRHealthComponent()
{
}


void UDRHealthComponent::ModifyHealth(int difference)
{
	UDRGameplayStatics::GetHUD(GetWorld())->SpawnFloatingDamageText(GetOwner(),FMath::Abs(difference), difference > 0);
	mCurrentHealth = FMath::Clamp(mCurrentHealth + difference, 0, mMaxHealth);
	mOnHealthChanged.Broadcast(mCurrentHealth);
	if(mCurrentHealth == 0)
	{
		mOnDied.Broadcast();
	}
}

void UDRHealthComponent::ApplyStats(UDRCharacterTemplate* charTemplate)
{
	mMaxHealth = charTemplate->MaxHealth;
	mCurrentHealth = mMaxHealth;
}
