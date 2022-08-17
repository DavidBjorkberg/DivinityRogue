// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility.h"
#include "DRCharacter.h"
void ADRAbility::Use(ADRCharacter* target)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *target->GetActorLabel());
}
