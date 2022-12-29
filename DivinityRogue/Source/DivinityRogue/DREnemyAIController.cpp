// Fill out your copyright notice in the Description page of Project Settings.


#include "DREnemyAIController.h"

#include "DRGameplayStatics.h"
#include "DRAbility.h"
#include "DRGameMode.h"

void ADREnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ADREnemyAIController::StartRequestAction()
{
	check(!GetWorldTimerManager().IsTimerActive(RequestActionTimer));
	GetWorldTimerManager().SetTimer(RequestActionTimer, this, &ADREnemyAIController::RequestAction,
	                                mRequestActionDelay);
}

void ADREnemyAIController::RequestAction()
{
	GetWorldTimerManager().ClearTimer(RequestActionTimer); // This shouldn't be necessary, timer has run out.

	if(mGameMode->IsGameOver())
	{
		mRoundSystem->EndTurn();
		return;
	}
	
	TArray<UDRAbilityTargetComponent*> allPlayerUnits = mGameMode->GetAllPlayerAbilityTargets();
	UDRGameplayStatics::SortComponentListByDistance(mOwner,allPlayerUnits);
	if (TryUseAbility()) return;
	if (mOwner->TryBasicAttack(allPlayerUnits[0])) return;
	if (TryMoveTo(allPlayerUnits[0])) return;
	mRoundSystem->EndTurn();
}

bool ADREnemyAIController::TryUseAbility()
{
	for (UDRAbility* ability : mOwner->GetAbilityComponent()->GetAbilities())
	{
		if (ability->CanAffordCast() && ability->TrySetRandomTargets())
		{
			mOwner->UseAbility(ability);
			return true;
		}
	}
	return false;
}


bool ADREnemyAIController::TryMoveTo(UDRAbilityTargetComponent* target)
{
	float distance = UDRGameplayStatics::GetDistanceToEdge2D(mOwner->GetActorLocation(), target);
	if (distance > mAdjacentToActorThreshold)
	{
		OrderMoveToActor(target);
		return true;
	}
	return false;
}

void ADREnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (Result.IsSuccess() && mOwner->GetStatsComponent()->GetStats().mCurrentActionPoints > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveCompleted"));
		StartRequestAction();
	}
}

void ADREnemyAIController::OnFinishedAttack()
{
	if (mOwner->GetStatsComponent()->GetStats().mCurrentActionPoints > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("FinishedAttack"));
		StartRequestAction();
	}
	Super::OnFinishedAttack();
}
