// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility_GroundTarget_Exclusive.h"
#include "DRAbility_Leap.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_Leap : public UDRAbility_GroundTarget_Exclusive
{
	GENERATED_BODY()
public:
	virtual void Use() override;
};
