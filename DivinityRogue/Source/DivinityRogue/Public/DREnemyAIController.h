// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAIController.h"
#include "DRGameMode.h"
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
	void RequestAction();
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
private:
	UPROPERTY()
	ADRGameMode* mGameMode;
};
