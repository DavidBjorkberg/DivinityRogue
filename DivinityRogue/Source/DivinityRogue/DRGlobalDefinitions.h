// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "DRGlobalDefinitions.generated.h"

USTRUCT(BlueprintType)
struct FAbilityStruct : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDRAbility> Ability;
};

UCLASS()
class DIVINITYROGUE_API UDRGlobalDefinitions : public UObject
{
	GENERATED_BODY()
};
