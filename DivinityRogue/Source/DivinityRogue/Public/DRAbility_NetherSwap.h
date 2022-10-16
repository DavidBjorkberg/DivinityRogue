// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility_MultiTarget.h"
#include "DRAbility_NetherSwap.generated.h"

UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_NetherSwap : public UDRAbility_MultiTarget
{
	GENERATED_BODY()
public:
	virtual void Use() override;
};
