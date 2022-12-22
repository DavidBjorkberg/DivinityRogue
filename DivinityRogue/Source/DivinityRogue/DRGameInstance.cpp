// Fill out your copyright notice in the Description page of Project Settings.


#include "DRGameInstance.h"

#include "DRPlayerCharacter.h"

void UDRGameInstance::InitializePlayerCharacters()
{
	for (int i = 0; i < mPlayerCharacterClasses.Num(); i++)
	{
		UDRCharacterTemplate* charTemplate = NewObject<UDRCharacterTemplate>(this, mPlayerCharacterClasses[i]);
		mPlayerCharacters.Add(charTemplate);
	}
}

void UDRGameInstance::InitializePlayerCharactersWithOverrides(TArray<ADRPlayerCharacter*> playerCharacters)
{
	for (int i = 0; i < playerCharacters.Num(); i++)
	{
		UDRCharacterTemplate* charTemplate = NewObject<UDRCharacterTemplate>(this, playerCharacters[i]->mCharacterTemplateOverride);
		mPlayerCharacters.Add(charTemplate);
	}
}
