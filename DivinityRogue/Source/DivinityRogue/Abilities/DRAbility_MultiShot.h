// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility_MultiTarget.h"
#include "DRAbility_MultiShot.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_MultiShot : public UDRAbility_MultiTarget
{
	GENERATED_BODY()
public:
	virtual void Use() override;
	virtual bool AIShouldUse() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	int mDamage;
};
