// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAIController.h"

#include "DRCharacter.h"

ADRAIController::ADRAIController()
{
}

void ADRAIController::BeginPlay()
{
	Super::BeginPlay();
	mOwner = Cast<ADRCharacter>(GetPawn());
}
void ADRAIController::OrderMoveToLocation(FVector targetLoc)
{
	MoveToLocation(targetLoc,5,false);
	mOwner->PlayRunAnimation();
}
void ADRAIController::OrderMoveToActor(AActor* targetActor)
{
	MoveToActor(targetActor,5,false);
	mOwner->PlayRunAnimation();
}
void ADRAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (Result.IsSuccess())
	{
		mOwner->PlayIdleAnimation();
		mOwner->ConsumeActionPoints(1);
		mOwner->EndTurnIfOutOfActionPoints();
	}
}
