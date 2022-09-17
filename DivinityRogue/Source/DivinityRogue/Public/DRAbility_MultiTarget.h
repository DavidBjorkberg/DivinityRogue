// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAbility_MultiTarget.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRAbility_MultiTarget : public UDRAbility
{
	GENERATED_BODY()
protected:
	virtual void OnLeftMouseDown() override;
	virtual bool TrySetRandomTargets() override;
	virtual bool CanCast() override;
	virtual void ClearSelection() override;
	UPROPERTY()
	TArray<ADRCharacter*> mTargetedCharacters;
	UPROPERTY(EditDefaultsOnly)
	int mNumberOfTargets;
private:
};
