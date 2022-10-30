// Fill out your copyright notice in the Description page of Project Settings.


#include "DRHealthComponent.h"

// Sets default values for this component's properties
UDRHealthComponent::UDRHealthComponent()
{
}


void UDRHealthComponent::ModifyHealth(int difference)
{
	mCurrentHealth = FMath::Clamp(mCurrentHealth + difference, 0, mMaxHealth);
	mOnHealthChanged.Broadcast(mCurrentHealth);
	if(mCurrentHealth == 0)
	{
		mOnDied.Broadcast();
	}
}

// Called when the game starts
void UDRHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	mCurrentHealth = mMaxHealth;
}
