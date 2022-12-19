// Fill out your copyright notice in the Description page of Project Settings.


#include "DRGameInstance.h"

void UDRGameInstance::CacheAllData()
{
	for(ADRCharacter* playerCharacter : mPlayerCharacters)
	{
		FCharacterSave characterSave;
		characterSave.Health = playerCharacter->GetHealthComponent()->GetMaxHealth();
	}
}

void UDRGameInstance::RefreshDataFromCache()
{
	mPlayerCharacters.Empty();
	
}
