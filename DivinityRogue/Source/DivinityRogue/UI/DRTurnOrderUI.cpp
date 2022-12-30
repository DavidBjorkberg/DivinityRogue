// Fill out your copyright notice in the Description page of Project Settings.


#include "DRTurnOrderUI.h"

#include "DRUnitInfo.h"

void UDRTurnOrderUI::NativeConstruct()
{
	Super::NativeConstruct();
	UDRTurnQueue* turnQueue = GetWorld()->GetSubsystem<UDRRoundSystem>()->GetTurnQueue();
	turnQueue->mOnCharacterAdded.AddDynamic(this, &UDRTurnOrderUI::OnCharacterAdded);
	turnQueue->mOnCharacterRemoved.AddDynamic(this, &UDRTurnOrderUI::OnCharacterRemoved);

}

void UDRTurnOrderUI::FillTurnList(TArray<ADRCharacter*> allCharacters)
{
	for(int i = 0; i  < allCharacters.Num(); i++)
	{
		AddUnit(allCharacters[i]);
	}
}

void UDRTurnOrderUI::OnCharacterAdded(ADRCharacter* newCharacter,int index)
{
	AddUnit(newCharacter);
}

void UDRTurnOrderUI::OnCharacterRemoved(int index)
{
	mTurnList->RemoveChildAt(index);
}

void UDRTurnOrderUI::AddUnit(ADRCharacter* character)
{
	UDRUnitInfo* newUnitInfo = CreateWidget<UDRUnitInfo>(this,mUnitInfoClass);
	newUnitInfo->Init(character);
	mTurnList->AddChild(newUnitInfo);
}
