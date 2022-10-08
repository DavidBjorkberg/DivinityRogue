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


USTRUCT(BlueprintType)
struct FAbilityInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FString mName;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FString mDescription;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TargetType mTargetType;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float mRange;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int mActionPointCost = 1;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int mCooldown = 1;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UTexture2D* mIcon;
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
	UTexture2D* GetIcon() const { return mAbilityInfo.mIcon; }
	float GetRange() const { return mAbilityInfo.mRange; }
	void SetOwner(ADRCharacter* owner) { mOwner = owner; }
protected:
	virtual UWorld* GetWorld() const override;
	UFUNCTION()
	virtual void OnLeftMouseDown() PURE_VIRTUAL(UDRAbility::OnLeftMouseDown,);
	virtual bool IsValidTarget(ADRCharacter* target);
	virtual void ClearSelection() PURE_VIRTUAL(UDRAbility::ClearSelection,;)
	virtual void OnAbilitySelected();
	virtual void OnAbilityDeselected();
	void DeselectAbility();
	bool CanAffordCast();
	bool IsInRange(ADRCharacter* target);
	bool IsInRange(FVector targetLocation);
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FAbilityInfo mAbilityInfo;
	UPROPERTY()
	ADRGameMode* mGameMode;
	UPROPERTY()
	UWorld* mWorld;
	UPROPERTY()
	ADRPlayerController* mPlayerController;
	UPROPERTY()
	ADRCharacter* mOwner;
	bool mIsSelected;
private:
	UFUNCTION()
	void OnSelectedAbilityChanged(UDRAbility* ability);
};
