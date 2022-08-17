// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAIController.h"
#include "DRMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "DRCharacter.generated.h"

UENUM()
enum class EAnimState :uint8
{
	IDLE,
	ATTACK,
	MOVE,
};

UCLASS()
class DIVINITYROGUE_API ADRCharacter : public APawn
{
	GENERATED_BODY()

public:
	ADRCharacter();
	void SetTargetLocation(FVector targetLoc);
	virtual void BeginPlay() override;
	int GetSpeed() const { return mSpeed; };
	UFUNCTION(BlueprintCallable)
	bool IsInAnimState(EAnimState state) { return state == mCurrentAnimState; }

	void SetAnimState(EAnimState newState) { mCurrentAnimState = newState; };
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* mRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRMovementComponent* mMovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* mSkeletalMeshComponent;
	UPROPERTY(EditAnywhere)
	int mSpeed;
private:
	UPROPERTY()
	ADRAIController* mController;
	EAnimState mCurrentAnimState;
};
