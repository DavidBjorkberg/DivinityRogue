// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAbility_GroundTarget.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRAbility_GroundTarget : public UDRAbility
{
	GENERATED_BODY()

protected:
	virtual void OnLeftMouseDown() override;
	virtual bool TrySetRandomTargets() override;
	virtual bool CanCast() override;
	virtual void ClearSelection() override;
	UPROPERTY()
	FVector mTargetLocation;
	
};
