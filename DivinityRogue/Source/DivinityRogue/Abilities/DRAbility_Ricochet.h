// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityTypes/DRAbility_SingleTarget_Bounce.h"
#include "DRAbility_Ricochet.generated.h"

UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_Ricochet : public UDRAbility_SingleTarget_Bounce
{
	GENERATED_BODY()
public:
	virtual void Use() override;
	virtual bool AIShouldUse() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	int mDamage;

};
