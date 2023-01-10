// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DRTurnQueue.generated.h"
class ADRCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCharacterAdded, ADRCharacter*, newCharacter, int, index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterRemoved, int, index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQueueInitialized);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FContinuedToNextCharacter);


UCLASS()
class DIVINITYROGUE_API UDRTurnQueue : public UObject
{
	GENERATED_BODY()
public:
	ADRCharacter* GetNext();
	void Remove(ADRCharacter* characterToRemove);
	void FillQueueFromWorld();
	int GetQueueSize() const { return mQueue.Num(); }
	ADRCharacter* GetCharacterAt(int index) { return mQueue[index]; }
	FCharacterAdded mOnCharacterAdded;
	FCharacterRemoved mOnCharacterRemoved;
	FQueueInitialized mOnQueueInitialized;
	FContinuedToNextCharacter mOnContinuedToNextCharacter;
private:
	void AddToEnd(ADRCharacter* characterToAdd);
	UPROPERTY()
	TArray<ADRCharacter*> mQueue;
	int mCurrentQueueIndex;
};
