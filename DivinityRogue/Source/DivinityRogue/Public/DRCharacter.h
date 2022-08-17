// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAIController.h"
#include "DRMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "DRCharacter.generated.h"

UCLASS()
class DIVINITYROGUE_API ADRCharacter : public APawn
{
	GENERATED_BODY()

public:
	ADRCharacter();
	void SetTargetLocation(FVector targetLoc);
	virtual void BeginPlay() override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRMovementComponent* mMovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* mSkeletalMeshComponent;
private:
	UPROPERTY()
	ADRAIController* mController;
};
