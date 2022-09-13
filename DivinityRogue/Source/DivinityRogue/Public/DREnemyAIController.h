// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAIController.h"
#include "DREnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API ADREnemyAIController : public ADRAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	void StartRequestAction();
	void RequestAction();
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	virtual void OnFinishedAttack() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	float mRequestActionDelay = 1;
private:
	FTimerHandle RequestActionTimer;
};
