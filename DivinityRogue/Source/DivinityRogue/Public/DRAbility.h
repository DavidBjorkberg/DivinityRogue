// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRPlayerController.h"
#include "DRAbility.generated.h"

UENUM()
enum class TargetType : uint8
{
	ALLY,
	ENEMY,
	ANY,
};

class ADRCharacter;
UCLASS(Blueprintable, Abstract)
class DIVINITYROGUE_API UDRAbility : public UObject
{
	GENERATED_BODY()
public:
	UDRAbility();
	virtual void PostInitProperties() override;
	virtual void Use();
	virtual bool CanCast()PURE_VIRTUAL(UDRAbility::CanCast,return true;)
	virtual bool TrySetRandomTargets() PURE_VIRTUAL(UDRAbility::SetRandomTargets,return true;)
	
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIcon() const { return mIcon; }

	float GetRange() const { return mRange; }
	void SetOwner(ADRCharacter* owner) { mOwner = owner; }
protected:
	virtual UWorld* GetWorld() const override;
	UFUNCTION()
	virtual void OnLeftMouseDown() PURE_VIRTUAL(UDRAbility::OnLeftMouseDown,);
	virtual bool IsValidTarget(ADRCharacter* target);
	virtual void ClearSelection() PURE_VIRTUAL(UDRAbility::ClearSelection,;)
	bool CanAffordCast();
	bool IsInRange(ADRCharacter* target);
	UPROPERTY(EditDefaultsOnly, Category= "DRAbility")
	TargetType mTargetType;
	UPROPERTY(EditDefaultsOnly, Category= "DRAbility")
	float mRange;
	UPROPERTY(EditDefaultsOnly, Category= "DRAbility")
	int mActionPointCost = 1;
	UPROPERTY(EditDefaultsOnly, Category= "DRAbility")
	UTexture2D* mIcon;
	UPROPERTY()
	ADRGameMode* mGameMode;
	UPROPERTY()
	ADRPlayerController* mPlayerController;
	UPROPERTY()
	ADRCharacter* mOwner;
private:
	UFUNCTION()
	void OnSelectedAbilityChanged(UDRAbility* ability);
	bool mIsSelected;
};
