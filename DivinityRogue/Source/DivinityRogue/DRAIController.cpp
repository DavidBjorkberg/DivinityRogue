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
	mRoundSystem = GetWorld()->GetSubsystem<UDRRoundSystem>();
}

void ADRAIController::OnFinishedAttack()
{
	GetWorld()->GetAuthGameMode<ADRGameMode>()->SetGameplayState(EGameplayState::PlanningPath);
	mOwner->GetAnimationComponent()->PlayIdleAnimation();
	mOwner->EndTurnIfOutOfActionPoints();
}

void ADRAIController::OrderMoveToLocation(FVector targetLoc)
{
	MoveToLocation(targetLoc, 0, false);
	mOwner->GetAnimationComponent()->PlayRunAnimation();
	mGameMode->SetGameplayState(EGameplayState::WalkingPath);
}

void ADRAIController::OrderMoveToActor(UDRAbilityTargetComponent* target)
{
	mOwner->GetAnimationComponent()->PlayRunAnimation();
	mGameMode->SetGameplayState(EGameplayState::WalkingPath);
	MoveToActor(target->GetOwner(), 150, false);
}

void ADRAIController::OrderAttackMoveToActor(UDRAbilityTargetComponent* target)
{
	OrderMoveToActor(target);
	mOnMoveCompleted = [this,target]()
	{
		if(!mOwner->TryBasicAttack(target))
		{
			mGameMode->SetGameplayState(EGameplayState::PlanningPath);
			mOwner->GetAnimationComponent()->PlayIdleAnimation();
		}
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
