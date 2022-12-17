// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAbility_NoTarget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_NoTarget : public UDRAbility
{
	GENERATED_BODY()
public:
	virtual bool TrySetRandomTargets() override;

protected:
	virtual void ClearSelection() override;
	virtual void OnLeftMouseDown() override;
};
