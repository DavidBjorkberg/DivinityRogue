// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.generated.h"

class ADRCharacter;
UCLASS(Abstract)
class DIVINITYROGUE_API ADRAbility : public AActor
{
	GENERATED_BODY()
public:
	virtual bool TryUse(ADRCharacter* user,ADRCharacter* target)PURE_VIRTUAL(ADRAbility::Use,return false;);
	float GetRange() const { return mRange; };
protected:
	bool IsInRange(ADRCharacter* user, ADRCharacter* target);
	UPROPERTY(EditDefaultsOnly, Category= "DRAbility")
	float mRange;
};
