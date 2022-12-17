// Fill out your copyright notice in the Description page of Project Settings.


#include "DREnemyCharacter.h"


ADREnemyCharacter::ADREnemyCharacter()
{
}

void ADREnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	FindComponentByClass<UDRAbilityTargetComponent>()->SetTeam(ETeam::ENEMY);
}


