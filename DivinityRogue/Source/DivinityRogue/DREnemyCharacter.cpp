// Fill out your copyright notice in the Description page of Project Settings.


#include "DREnemyCharacter.h"


ADREnemyCharacter::ADREnemyCharacter()
{
}

void ADREnemyCharacter::BeginPlay()
{
	UDRCharacterTemplate* charTemplate = NewObject<UDRCharacterTemplate>(this, mCharacterTemplateOverride);
	Initialize(charTemplate);
	FindComponentByClass<UDRAbilityTargetComponent>()->SetTeam(ETeam::ENEMY);
	Super::BeginPlay();
	
}


