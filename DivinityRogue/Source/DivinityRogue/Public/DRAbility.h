// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.generated.h"

UENUM()
enum class TargetType : uint8
{
	ALLY,
	ENEMY,
	ANY,
};
class ADRCharacter;
UCLASS(Blueprintable)
class DIVINITYROGUE_API UDRAbility : public UObject
{
	GENERATED_BODY()
public:
	virtual void Use(ADRCharacter* user, ADRCharacter* target);
	bool CanCast(ADRCharacter* user,ADRCharacter* target);
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIcon() const { return mIcon; }
	float GetRange() const { return mRange; }

protected:
	bool IsInRange(ADRCharacter* user, ADRCharacter* target);
	bool IsValidTarget(ADRCharacter* user, ADRCharacter* target);
	UPROPERTY(EditDefaultsOnly, Category= "DRAbility")
	TargetType mTargetType;
	UPROPERTY(EditDefaultsOnly, Category= "DRAbility")
	float mRange;
	UPROPERTY(EditDefaultsOnly, Category= "DRAbility")
	int mActionPointCost = 1;
	UPROPERTY(EditDefaultsOnly, Category= "DRAbility")
	UTexture2D* mIcon;
private:
};
