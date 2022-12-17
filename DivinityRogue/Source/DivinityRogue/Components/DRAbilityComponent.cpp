// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbilityComponent.h"

#include "DRAbility_BasicAttack.h"
#include "DRCharacter.h"


UDRAbilityComponent::UDRAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UDRAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnStarterAbilities();
}

void UDRAbilityComponent::SpawnStarterAbilities()
{
	mAbilities.Empty();
	for (TSubclassOf<UDRAbility> ability : mAbilityClasses)
	{
		UDRAbility* spawnedAbility = NewObject<UDRAbility>(GetWorld(), ability);
		spawnedAbility->SetOwner(Cast<ADRCharacter>(GetOwner()));
		mAbilities.Add(spawnedAbility);
	}
	UDRAbility* spawnedAbility = NewObject<UDRAbility>(GetOwner(), mBasicAttackClass);
	spawnedAbility->SetOwner(Cast<ADRCharacter>(GetOwner()));
	mBasicAttack = Cast<UDRAbility_BasicAttack>(spawnedAbility);
}
