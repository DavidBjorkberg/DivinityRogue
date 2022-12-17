// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAbility_MultiTarget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_MultiTarget : public UDRAbility
{
	GENERATED_BODY()
protected:
	virtual void OnLeftMouseDown() override;
	virtual bool TrySetRandomTargets() override;
	virtual void ClearSelection() override;
	virtual bool IsValidTarget(UDRAbilityTargetComponent* target) override;
	UPROPERTY()
	TArray<UDRAbilityTargetComponent*> mTargets;
	UPROPERTY(EditDefaultsOnly)
	int mNumberOfTargets;
private:
};
