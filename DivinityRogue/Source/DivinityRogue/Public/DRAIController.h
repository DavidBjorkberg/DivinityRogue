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
	// void MoveToLocation(FVector targetLoc);
	// void MoveToActor(AActor* targetActor)
	void OrderMoveToLocation(FVector targetLoc);
	void OrderMoveToActor(AActor* targetActor);
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	virtual void BeginPlay() override;
protected:
	UPROPERTY()
	ADRCharacter* mOwner;
private:

};
