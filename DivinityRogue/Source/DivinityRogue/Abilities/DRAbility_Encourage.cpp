// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_Encourage.h"

void UDRAbility_Encourage::Use()
{
	Super::Use();
	for(int i = 0; i < mTargets.Num(); i++)
	{
		//TODO: Heighten stats
	}
}

bool UDRAbility_Encourage::AIShouldUse()
{
	return Super::AIShouldUse();
}
