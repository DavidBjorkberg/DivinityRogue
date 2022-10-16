// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility_SingleTarget.h"
#include "DRAbility_Slam.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_Slam : public UDRAbility_SingleTarget
{
	GENERATED_BODY()
public:
	virtual void Use() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	int mDamage;

};
