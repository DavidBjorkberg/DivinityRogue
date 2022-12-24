// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAbility_BasicAttack.h"
#include "DRCharacterAnimInstance.h"
#include "UObject/Object.h"
#include "DRCharacterTemplate.generated.h"

UCLASS(BlueprintType,Blueprintable)
class DIVINITYROGUE_API UDRCharacterTemplate : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FText Name;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int MaxHealth = 40;
	int CurrentHealth;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int Speed = 5;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int MaxActionPoints = 4;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int StartActionPoints = 3;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int ActionPointsPerTurn = 2;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int MovementSpeed = 6;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int Movement = 250;
	UPROPERTY(BlueprintReadWrite)
	TArray<TSubclassOf<UDRAbility>> AbilityClasses;
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UDRAbility_BasicAttack> BasicAttackClass;
	UPROPERTY(BlueprintReadWrite)
	USkeletalMesh* Mesh;
	UPROPERTY(BlueprintReadWrite)
	UMaterialInterface* MeshMaterial;
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UDRCharacterAnimInstance> AnimInstance;
	
};
