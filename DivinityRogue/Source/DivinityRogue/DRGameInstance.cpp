// Fill out your copyright notice in the Description page of Project Settings.


#include "DRGameInstance.h"


void UDRGameInstance::InitializePlayerCharacters()
{
	for (int i = 0; i < mPlayerCharacterClasses.Num(); i++)
	{
		UDRCharacterTemplate* charTemplate = NewObject<UDRCharacterTemplate>(this, mPlayerCharacterClasses[i]);
		charTemplate->CurrentHealth = charTemplate->MaxHealth;
		mPlayerCharacters.Add(charTemplate);
	}
}

void UDRGameInstance::InitializePlayerCharactersWithOverrides(TArray<ADRCharacter*> playerCharacters)
{
	for (int i = 0; i < playerCharacters.Num(); i++)
	{
		UDRCharacterTemplate* charTemplate = NewObject<UDRCharacterTemplate>(this, playerCharacters[i]->mCharacterTemplateOverride);
		charTemplate->CurrentHealth = charTemplate->MaxHealth;
		mPlayerCharacters.Add(charTemplate);
	}
}
