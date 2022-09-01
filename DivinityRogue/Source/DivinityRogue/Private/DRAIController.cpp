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
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
}

void ADRAIController::OnFinishedAttack()
{
	mOwner->PlayIdleAnimation();
	mOwner->EndTurnIfOutOfActionPoints();
}

void ADRAIController::OrderMoveToLocation(FVector targetLoc)
{
	MoveToLocation(targetLoc, 5, false);
	mOwner->PlayRunAnimation();
	mGameMode->SetGameplayState(EGameplayState::WalkingPath);
}

void ADRAIController::OrderMoveToActor(AActor* targetActor)
{
	mOwner->PlayRunAnimation();
	mGameMode->SetGameplayState(EGameplayState::WalkingPath);
	MoveToActor(targetActor, 5, false);
}

void ADRAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (Result.IsSuccess())
	{
		mGameMode->SetGameplayState(EGameplayState::PlanningPath);
		mOwner->PlayIdleAnimation();
	}
}
