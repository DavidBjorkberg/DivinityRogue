// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAIController.h"

#include "DRGameMode.h"
#include "BehaviorTree/BlackboardComponent.h"

ADRAIController::ADRAIController()
{
}

void ADRAIController::SetTargetLocation(FVector targetLoc)
{
	mBlackboard->SetValueAsVector("TargetLocation", targetLoc);
	mBlackboard->SetValueAsEnum("State", (int)EAIState::MOVE);
	mOwner->SetAnimState(EAnimState::MOVE);
}

void ADRAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (Result.IsSuccess())
	{
		mBlackboard->SetValueAsEnum("State", (int)EAIState::IDLE);
		mOwner->SetAnimState(EAnimState::IDLE);
		GetWorld()->GetAuthGameMode<ADRGameMode>()->OnActionCompleted();
	}
}

void ADRAIController::BeginPlay()
{
	Super::BeginPlay();
	mBlackboard = GetBlackboardComponent();
	mOwner = Cast<ADRCharacter>(GetPawn());
}
