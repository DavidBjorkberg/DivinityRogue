// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbilityTargetComponent.h"
#include "DRAbility_SingleTarget.h"
#include "DRAbility_SingleTarget_AOE.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_SingleTarget_AOE : public UDRAbility_SingleTarget
{
	GENERATED_BODY()
protected:
	TArray<UDRAbilityTargetComponent*> GetNearbyTargets();
	UPROPERTY(EditDefaultsOnly)
	float mRadius;
};
