// Fill out your copyright notice in the Description page of Project Settings.


#include "DRSelectRewardUI.h"

void UDRSelectRewardUI::GetRandomAbilities(TSubclassOf<UDRAbility>& ability1, TSubclassOf<UDRAbility>& ability2,
                                           TSubclassOf<UDRAbility>& ability3)
{
	TArray<TSubclassOf<UDRAbility>> allAbilities;
	//Find all asset classes and connect them to their target class
	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		if (ClassIt->IsChildOf(UDRAbility::StaticClass()) && !ClassIt->HasAnyClassFlags(CLASS_Abstract))
		{
			allAbilities.Add(*ClassIt);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		int index = FMath::RandRange(0, allAbilities.Num());
		switch (i)
		{
		case 0:
			ability1 = allAbilities[index];
			break;
		case 1:
			ability2 = allAbilities[index];
			break;
		case 2:
			ability3 = allAbilities[index];
			break;
		default:
			break;
		}
		allAbilities.RemoveAt(index);
	}
}
