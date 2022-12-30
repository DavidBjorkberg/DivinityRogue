// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DRTurnQueue.generated.h"
class ADRCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCharacterAdded, ADRCharacter*, newCharacter, int, index);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterRemoved, int, index);

UCLASS()
class DIVINITYROGUE_API UDRTurnQueue : public UObject
{
	GENERATED_BODY()
public:
	ADRCharacter* GetAndRemoveNext();
	void AddToEnd(ADRCharacter* characterToAdd);
	void Remove(ADRCharacter* characterToRemove);
	void FillQueueFromWorld();
	bool IsEmpty() const { return mQueue.Num() == 0; }
	FCharacterAdded mOnCharacterAdded;
	FCharacterRemoved mOnCharacterRemoved;
private:
	UPROPERTY()
	TArray<ADRCharacter*> mQueue;
};
