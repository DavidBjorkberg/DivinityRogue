// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAbility_SingleTarget.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRAbility_SingleTarget : public UDRAbility
{
	GENERATED_BODY()

protected:
	virtual void OnLeftMouseDown() override;
	virtual bool TrySetRandomTargets() override;
	virtual bool CanCast() override;
	virtual void ClearSelection() override;
	UPROPERTY()
	ADRCharacter* mTarget;

private:
};
