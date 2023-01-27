// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRRoundSystem.h"
#include "Sound/SoundCue.h"
#include "DRAbility.generated.h"

class UDRAbilityTargetComponent;
class ADRPlayerController;
class ADRGameMode;
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText mName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText mDescription;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TargetType mTargetType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float mRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int mActionPointCost = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int mCooldown = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
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
	virtual bool TrySetRandomTargets() PURE_VIRTUAL(UDRAbility::SetRandomTargets, return true;)

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIcon() const { return mAbilityInfo.mIcon; }

	float GetRange() const { return mAbilityInfo.mRange; }
	void SetOwner(ADRCharacter* owner) { mOwner = owner; }
	bool IsInRange(UDRAbilityTargetComponent* target);
	virtual bool IsTargetCorrectTeam(UDRAbilityTargetComponent* selectableComp);
	bool CanAffordCast();
	virtual bool AIShouldUse() PURE_VIRTUAL(UDRAbility::AIShouldUse, return true;)
	bool IsOnCooldown() const { return mRemainingCooldown > 0; }
	FAbilityInfo GetAbilityInfo() const { return mAbilityInfo; }
	//Used for rotating the user to the desired rotation
	virtual FVector GetTargetLocation();
	virtual bool ShouldRotateUser() const { return true; }
	bool IsRanged() const {return GetRange() >= mRangedAttackThreshold;}
protected:
	virtual UWorld* GetWorld() const override;
	UFUNCTION()
	virtual void OnLeftMouseDown() PURE_VIRTUAL(UDRAbility::OnLeftMouseDown,);
	virtual void ClearSelection() PURE_VIRTUAL(UDRAbility::ClearSelection, ;)
	virtual void OnAbilitySelected();
	virtual void OnAbilityDeselected();
	virtual bool IsValidTarget(UDRAbilityTargetComponent* target);
	TArray<UDRAbilityTargetComponent*> GetAllValidTargetsInRadius(FVector location, float radius, bool ignoreSelf); 
	void DeselectAbility();
	bool IsInRange(FVector targetLocation);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAbilityInfo mAbilityInfo;
	UPROPERTY(EditDefaultsOnly)
	USoundCue* mOnUsedSound;
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* mOnUsedParticleEffect;
	UPROPERTY(BlueprintReadOnly)
	int mRemainingCooldown;
	bool mIsSelected;
	
	UPROPERTY()
	ADRGameMode* mGameMode;
	UPROPERTY()
	UWorld* mWorld;
	UPROPERTY()
	UDRRoundSystem* mRoundSystem;
	UPROPERTY()
	ADRPlayerController* mPlayerController;
	UPROPERTY()
	ADRCharacter* mOwner;
private:
	float mRangedAttackThreshold = 400;
	UFUNCTION()
	void OnSelectedAbilityChanged(UDRAbility* ability);
	UFUNCTION()
	void OnNewRound();
};
