// Fill out your copyright notice in the Description page of Project Settings.


#include "DRPlayerCharacter.h"

ADRPlayerCharacter::ADRPlayerCharacter()
{
}

void ADRPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	mAbilityTargetComponent->SetTeam(ETeam::PLAYER);
}
