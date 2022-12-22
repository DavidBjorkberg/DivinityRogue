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
	UPROPERTY(EditDefaultsOnly)
	FText Name;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int MaxHealth = 40;
	int CurrentHealth;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int Speed = 5;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int MaxActionPoints = 4;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int StartActionPoints = 3;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int ActionPointsPerTurn = 2;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int MovementSpeed = 6;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int Movement = 250;
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UDRAbility>> AbilityClasses;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDRAbility_BasicAttack> BasicAttackClass;
	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* Mesh;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* MeshMaterial;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDRCharacterAnimInstance> AnimInstance;
	
};
