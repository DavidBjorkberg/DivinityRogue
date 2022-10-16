// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRCircleDecal.h"
#include "Tickable.h"
#include "DRAbility_GroundTarget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DIVINITYROGUE_API UDRAbility_GroundTarget : public UDRAbility, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual TStatId GetStatId() const override
	{
		return UObject::GetStatID();
	}

protected:
	virtual void Tick(float DeltaTime) override;
	virtual bool TrySetRandomTargets() override;
	virtual bool CanCast() override;
	virtual void ClearSelection() override;
	virtual void OnAbilitySelected() override;
	virtual void OnAbilityDeselected() override;
	virtual bool IsOnValidArea();
	void SetDecalMaterial(UMaterialInterface* newMaterial);
	UPROPERTY(EditDefaultsOnly)
	float mRadius;
	UPROPERTY()
	FVector mTargetLocation;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADRCircleDecal> mDecalActor;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* mDecalMaterial;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* mInvalidDecalMaterial;
	UPROPERTY()
	ADRCircleDecal* mDecalActorInst;
};
