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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void RequestPathMove(const FVector& MoveVelocity) override;
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	virtual bool CanStartPathFollowing() const override;
	void SetDesiredRotation(FRotator desiredRotation) { mDesiredRotation = desiredRotation; };
protected:
	UPROPERTY(EditDefaultsOnly)
	int mMovementSpeed = 6;
	UPROPERTY(EditDefaultsOnly)
	int mRotationRate = 4;
private:
	FRotator mDesiredRotation;
};
