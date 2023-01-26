// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility_NoTarget_AOE.h"
#include "DRAbility_Encourage.generated.h"

UCLASS()
class DIVINITYROGUE_API UDRAbility_Encourage : public UDRAbility_NoTarget_AOE
{
	GENERATED_BODY()
public:
	virtual void Use() override;
	virtual bool AIShouldUse() override;
};
