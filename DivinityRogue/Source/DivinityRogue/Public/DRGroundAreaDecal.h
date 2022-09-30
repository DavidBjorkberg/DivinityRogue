// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DRGroundAreaDecal.generated.h"

UCLASS()
class DIVINITYROGUE_API ADRGroundAreaDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	ADRGroundAreaDecal();
	UFUNCTION(BlueprintImplementableEvent)
	void SetRadius(float radius);
	UFUNCTION(BlueprintImplementableEvent)
	UDecalComponent* GetDecalComponent();
};
