// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.generated.h"

class ADRCharacter;
UCLASS()
class DIVINITYROGUE_API UDRAbility : public UObject
{
	GENERATED_BODY()
public:
	virtual bool TryUse(ADRCharacter* user,ADRCharacter* target);
	float GetRange() const { return mRange; }
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIcon() const {return mIcon;}
protected:
	bool IsInRange(ADRCharacter* user, ADRCharacter* target);
	UPROPERTY(EditDefaultsOnly, Category= "DRAbility")
	float mRange;
	UPROPERTY(EditDefaultsOnly, Category= "DRAbility")
	UTexture2D* mIcon;
};
