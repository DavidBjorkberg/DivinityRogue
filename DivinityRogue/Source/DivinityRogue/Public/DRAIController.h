// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DRAIController.generated.h"

class ADRCharacter;
UENUM(BlueprintType)
enum class EAIState : uint8
{
	IDLE UMETA(DisplayName = IDLE),
	ATTACK UMETA(DisplayName = ATTACK),
	MOVE UMETA(DisplayName = MOVE),
};
UCLASS()
class DIVINITYROGUE_API ADRAIController : public AAIController
{
	GENERATED_BODY()
public:
	ADRAIController();
	void SetTargetLocation(FVector targetLoc);
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	UBlackboardComponent* mBlackboard;
	UPROPERTY()
	ADRCharacter* mOwner;
};
