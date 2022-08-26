// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "DREnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API ADREnemyCharacter : public ADRCharacter
{
	GENERATED_BODY()
public:
	ADREnemyCharacter();
	virtual void BeginPlay() override;
	virtual void OnFinishedAttack() override;
};
