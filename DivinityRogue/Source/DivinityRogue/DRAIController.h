// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DRGameMode.h"
#include "DRAIController.generated.h"
class ADRGameMode;
class ADRCharacter;
UENUM(BlueprintType)
enum class EAIState : uint8
{
	IDLE,
	ATTACK,
	MOVE,
};
UCLASS()
class DIVINITYROGUE_API ADRAIController : public AAIController
{
	GENERATED_BODY()
public:
	ADRAIController();
	void OrderMoveToLocation(FVector targetLoc);
	void OrderMoveToActor(UDRAbilityTargetComponent* target);
	void OrderAttackMoveToActor(UDRAbilityTargetComponent* target);
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnFinishedAttack();
protected:
	UPROPERTY()
	ADRCharacter* mOwner;
	UPROPERTY()
	ADRGameMode* mGameMode;
	UPROPERTY()
	UDRRoundSystem* mRoundSystem;
private:
	TFunction<void()> mOnMoveCompleted;

};
