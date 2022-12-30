// Fill out your copyright notice in the Description page of Project Settings.


#include "DRTurnQueue.h"

#include "DRGameplayStatics.h"

ADRCharacter* UDRTurnQueue::GetAndRemoveNext()
{
	check(mQueue.Num() > 0);
	ADRCharacter* nextCharacter = mQueue[0];
	Remove(nextCharacter);
	return nextCharacter;
}

void UDRTurnQueue::AddToEnd(ADRCharacter* characterToAdd)
{
	mQueue.Add(characterToAdd);
	mOnCharacterAdded.Broadcast(characterToAdd,mQueue.Num() - 1);
}

void UDRTurnQueue::Remove(ADRCharacter* characterToRemove)
{
	for (int i = 0; i < mQueue.Num(); i++)
	{
		if (mQueue[i] == characterToRemove)
		{
			mQueue.RemoveAt(i);
			mOnCharacterRemoved.Broadcast(i);
			return;
		}
	}
}

void UDRTurnQueue::FillQueueFromWorld()
{
	mQueue.Empty();
	TArray<ADRCharacter*> allAliveCharacters;
	UDRGameplayStatics::GetAllAliveCharacters(GetWorld(), allAliveCharacters);
	allAliveCharacters.Sort([](const ADRCharacter& a, const ADRCharacter& b)
	{
		return a.GetStatsComponent()->GetStats().mSpeed > b.GetStatsComponent()->GetStats().mSpeed;
	});
	for(int i = 0; i < allAliveCharacters.Num(); i++)
	{
		AddToEnd(allAliveCharacters[i]);
	}
}
