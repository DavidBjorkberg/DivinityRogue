// Fill out your copyright notice in the Description page of Project Settings.


#include "DRPartyUI.h"

#include "DRGameplayStatics.h"
#include "DRTurnOrderUnitInfo.h"

void UDRPartyUI::NativeConstruct()
{
	Super::NativePreConstruct();
	TArray<ADRCharacter*> allPlayerCharacters;
	UDRGameplayStatics::GetAllPlayerCharacters(GetWorld(), allPlayerCharacters);
	for(int i = 0; i < allPlayerCharacters.Num();i++)
	{
		AddCharacter(allPlayerCharacters[i]);
	}
	GetWorld()->GetAuthGameMode<ADRGameMode>()->mOnCharacterSpawned.AddDynamic(this, &UDRPartyUI::AddCharacter);
}

void UDRPartyUI::AddCharacter(ADRCharacter* characterToAdd)
{
	UDRPartyUnitInfo* newUnitInfo = CreateWidget<UDRPartyUnitInfo>(this, mUnitInfoClass);
	newUnitInfo->Init(characterToAdd);
	mUnitInfos->AddChild(newUnitInfo);
}
