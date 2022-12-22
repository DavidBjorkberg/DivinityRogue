// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbilityComponent.h"

#include "DRAbility_BasicAttack.h"
#include "DRCharacter.h"


UDRAbilityComponent::UDRAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UDRAbilityComponent::ApplyTemplate(UDRCharacterTemplate* charTemplate)
{
	for (TSubclassOf<UDRAbility> ability : charTemplate->AbilityClasses)
	{
		UDRAbility* spawnedAbility = NewObject<UDRAbility>(GetWorld(), ability);
		spawnedAbility->SetOwner(Cast<ADRCharacter>(GetOwner()));
		mAbilities.Add(spawnedAbility);
	}
	UDRAbility* spawnedAbility = NewObject<UDRAbility>(GetOwner(), charTemplate->BasicAttackClass);
	spawnedAbility->SetOwner(Cast<ADRCharacter>(GetOwner()));
	mBasicAttack = Cast<UDRAbility_BasicAttack>(spawnedAbility);
}
