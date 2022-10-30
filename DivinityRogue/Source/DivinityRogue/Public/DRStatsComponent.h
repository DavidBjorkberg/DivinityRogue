// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DRStatsComponent.generated.h"

USTRUCT(BlueprintType)
struct FCharacterBaseStats
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "DRCharacter")
	int mSpeed = 5;
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	int mMaxActionPoints = 2;
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	int mStartActionPoints = 2;
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	int mActionPointsPerTurn = 2;
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	int mMovementSpeed = 6;
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	int mMovement = 2;
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	FString mName;
};

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, DisplayName="Name")
	FString mName;
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
	void UpdateEnergy(int difference);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FCharacterStats GetStats() const { return mStats; }
	UPROPERTY(BlueprintAssignable)
	FEnergyChange mOnEnergyChange;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCharacterBaseStats mBaseStats;
	UPROPERTY(BlueprintReadOnly)
	FCharacterStats mStats;
private:
	void ApplyBaseStats();
};
