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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Stats")
	int MaxHealth = 40;
	int CurrentHealth;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Stats")
	int Speed = 5;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Stats")
	int MaxActionPoints = 4;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Stats")
	int StartActionPoints = 3;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Stats")
	int ActionPointsPerTurn = 2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Stats")
	int MovementSpeed = 6;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Stats")
	int Movement = 250;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TSubclassOf<UDRAbility>> AbilityClasses;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UDRAbility_BasicAttack> BasicAttackClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USkeletalMesh* Mesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMesh* LeftWeapon;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMesh* RightWeapon;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UDRCharacterAnimInstance> AnimInstance;
	
};
