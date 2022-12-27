// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAbilityTargetComponent.h"
#include "DRAbility_SingleTarget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_SingleTarget : public UDRAbility
{
	GENERATED_BODY()

protected:
	virtual void OnLeftMouseDown() override;
	virtual bool TrySetRandomTargets() override;
	virtual void ClearSelection() override;
	virtual bool IsValidTarget(UDRAbilityTargetComponent* target) override;
	virtual FVector GetTargetLocation() { return mTarget->GetOwner()->GetActorLocation(); }
	UPROPERTY()
	UDRAbilityTargetComponent* mTarget;
private:
};
