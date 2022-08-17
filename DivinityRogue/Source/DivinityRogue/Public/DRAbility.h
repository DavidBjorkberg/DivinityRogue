// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.generated.h"

class ADRCharacter;
UCLASS()
class DIVINITYROGUE_API ADRAbility : public AActor
{
	GENERATED_BODY()
public:
	void Use(ADRCharacter* target);
	float GetRange() const { return mRange; };
protected:
	UPROPERTY(EditDefaultsOnly)
	float mRange;
};
