// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DRCircleDecal.generated.h"

UCLASS()
class DIVINITYROGUE_API ADRCircleDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	ADRCircleDecal();
	UFUNCTION(BlueprintImplementableEvent)
	void SetRadius(float radius);
	UFUNCTION(BlueprintImplementableEvent)
	UDecalComponent* GetDecalComponent();
};
