// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility_GroundTarget.h"
#include "DRAbility_GroundTarget_Exclusive.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_GroundTarget_Exclusive : public UDRAbility_GroundTarget
{
	GENERATED_BODY()
public:
	virtual void OnLeftMouseDown() override;
protected:
	virtual bool IsOnValidArea() override;

};
