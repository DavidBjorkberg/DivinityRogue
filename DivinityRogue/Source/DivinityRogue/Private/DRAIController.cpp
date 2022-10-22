// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAIController.h"

#include "DRCharacter.h"
#include "DRGameMode.h"

ADRAIController::ADRAIController()
{
}

void ADRAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	mOwner = Cast<ADRCharacter>(InPawn);
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
}

void ADRAIController::OnFinishedAttack()
{
	GetWorld()->GetAuthGameMode<ADRGameMode>()->SetGameplayState(EGameplayState::PlanningPath);
	mOwner->GetAnimationComponent()->PlayIdleAnimation();
	mOwner->EndTurnIfOutOfActionPoints();
}

void ADRAIController::OrderMoveToLocation(FVector targetLoc)
{
	MoveToLocation(targetLoc, 5, false);
	mOwner->GetAnimationComponent()->PlayRunAnimation();
	mGameMode->SetGameplayState(EGameplayState::WalkingPath);
}

void ADRAIController::OrderMoveToActor(ADRCharacter* targetActor)
{
	mOwner->GetAnimationComponent()->PlayRunAnimation();
	mGameMode->SetGameplayState(EGameplayState::WalkingPath);
	MoveToActor(targetActor, 5, false);
}

void ADRAIController::OrderAttackMoveToActor(ADRCharacter* targetActor)
{
	OrderMoveToActor(targetActor);
	mOnMoveCompleted = [this,targetActor]()
	{
		mOwner->BasicAttack(targetActor);
	};
}

void ADRAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (Result.IsSuccess())
	{
		if (mOnMoveCompleted != nullptr)
		{
			mOnMoveCompleted();
		}
		else
		{
			mGameMode->SetGameplayState(EGameplayState::PlanningPath);
			mOwner->GetAnimationComponent()->PlayIdleAnimation();
		}
	}
	mOnMoveCompleted = nullptr;
}
