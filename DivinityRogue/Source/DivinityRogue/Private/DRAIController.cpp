// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

ADRAIController::ADRAIController()
{
}

void ADRAIController::SetTargetLocation(FVector targetLoc)
{
	GetBlackboardComponent()->SetValueAsVector("TargetLocation",targetLoc);
	GetBlackboardComponent()->SetValueAsEnum("State",(int)EAIState::MOVE);
}			

void ADRAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	GetBlackboardComponent()->SetValueAsEnum("State",(int)EAIState::IDLE);
	Super::OnMoveCompleted(RequestID, Result);
}
