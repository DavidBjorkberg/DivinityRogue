// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DRLineDecal.generated.h"

UCLASS()
class DIVINITYROGUE_API ADRLineDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	ADRLineDecal();
	UFUNCTION(BlueprintImplementableEvent)
	void SetLength(float length);
	UFUNCTION(BlueprintImplementableEvent)
	UDecalComponent* GetDecalComponent();
protected:
	UPROPERTY(EditDefaultsOnly)
	float mLength;
};
