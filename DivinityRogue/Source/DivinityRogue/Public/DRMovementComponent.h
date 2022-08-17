// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "DRMovementComponent.generated.h"

UCLASS()
class DIVINITYROGUE_API UDRMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
public:
	virtual void RequestPathMove(const FVector& MoveVelocity) override;
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	virtual bool CanStartPathFollowing() const override;
	protected:
	UPROPERTY(EditDefaultsOnly)
		int mMovementSpeed;
};


