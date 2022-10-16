// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility_SingleTarget.h"
#include "DRAbility_Charge.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRAbility_Charge : public UDRAbility_SingleTarget
{
	GENERATED_BODY()
public:
	virtual void Use() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	int mDamage;
};
