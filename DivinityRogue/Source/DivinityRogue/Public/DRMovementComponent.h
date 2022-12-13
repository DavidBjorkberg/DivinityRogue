// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "DRMovementComponent.generated.h"

class ADRCharacter;
UCLASS()
class DIVINITYROGUE_API UDRMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	void SetDesiredRotation(FRotator desiredRotation) { mDesiredRotation = desiredRotation; };
	int GetEnergyCostToMouse();
	float mDistanceLeftUntilEnergyCost;
protected:
	UPROPERTY(EditDefaultsOnly)
	int mRotationRate = 4;
private:

	UFUNCTION()
	void OnTurnStart();
	UPROPERTY()
	ADRCharacter* mOwner;
	UPROPERTY()
	ADRGameMode* mGameMode;
	FRotator mDesiredRotation;
	int mMovementSpeed;
};

