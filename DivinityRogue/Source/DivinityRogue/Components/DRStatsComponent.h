// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacterTemplate.h"
#include "Components/ActorComponent.h"
#include "DRStatsComponent.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, DisplayName="Speed")
	int mSpeed;
	UPROPERTY(BlueprintReadOnly, DisplayName="Movement Speed")
	int mMovementSpeed;
	UPROPERTY(BlueprintReadOnly, DisplayName="Movement")
	int mMovement;
	UPROPERTY(BlueprintReadOnly, DisplayName="Max Energy")
	int mMaxActionPoints;
	UPROPERTY(BlueprintReadOnly, DisplayName="Current Energy")
	int mCurrentActionPoints;
	UPROPERTY(BlueprintReadOnly, DisplayName="Start Energy")
	int mStartActionPoints;
	UPROPERTY(BlueprintReadOnly, DisplayName="Energy per turn")
	int mActionPointsPerTurn;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnergyChange, int, newEnergy);

UCLASS()
class DIVINITYROGUE_API UDRStatsComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UDRStatsComponent();
	void ModifyEnergy(int difference);
	void ApplyStats(UDRCharacterTemplate* charTemplate);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FCharacterStats GetStats() const { return mStats; }
	UPROPERTY(BlueprintAssignable)
	FEnergyChange mOnEnergyChange;
protected:
	UPROPERTY(BlueprintReadOnly)
	FCharacterStats mStats;
};
