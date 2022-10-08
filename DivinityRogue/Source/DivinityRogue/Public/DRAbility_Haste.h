// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility_SingleTarget.h"
#include "DRAbility_Haste.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRAbility_Haste : public UDRAbility_SingleTarget
{
	GENERATED_BODY()
public:
	virtual void Use() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	int mEnergyIncrease;
};
