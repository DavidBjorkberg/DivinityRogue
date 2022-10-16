// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAbility_LineTarget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_LineTarget : public UDRAbility, public FTickableGameObject
{
	GENERATED_BODY()
public:
	virtual TStatId GetStatId() const override
	{
		return UObject::GetStatID();
	}
protected:
	virtual void Tick(float DeltaTime) override;

};
