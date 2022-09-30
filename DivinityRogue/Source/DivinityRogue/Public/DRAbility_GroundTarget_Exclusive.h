// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility_GroundTarget.h"
#include "DRAbility_GroundTarget_Exclusive.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRAbility_GroundTarget_Exclusive : public UDRAbility_GroundTarget
{
	GENERATED_BODY()
public:
	virtual void OnLeftMouseDown() override;
	virtual void Tick(float DeltaTime) override;

};
