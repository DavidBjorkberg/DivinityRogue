// Fill out your copyright notice in the Description page of Project Settings.


#include "DRSelectRewardUI.h"

#include "DRGlobalDefinitions.h"

void UDRSelectRewardUI::GetRandomAbilities(TSubclassOf<UDRAbility>& ability1, TSubclassOf<UDRAbility>& ability2,
                                           TSubclassOf<UDRAbility>& ability3)
{
	TArray<FAbilityStruct*> allAbilities;
	abilityDataTable->GetAllRows<FAbilityStruct>("AbilityDataTable",allAbilities);

	for (int i = 0; i < 3; i++)
	{
		int index = FMath::RandRange(0, allAbilities.Num()-1);
		switch (i)
		{
		case 0:
			ability1 = allAbilities[index]->Ability;
			break;
		case 1:
			ability2 = allAbilities[index]->Ability;
			break;
		case 2:
			ability3 = allAbilities[index]->Ability;
			break;
		default:
			break;
		}
		allAbilities.RemoveAt(index);
	}
}
