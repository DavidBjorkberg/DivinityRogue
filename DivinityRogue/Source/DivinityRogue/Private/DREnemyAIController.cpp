// Fill out your copyright notice in the Description page of Project Settings.


#include "DREnemyAIController.h"

#include "DRGameplayStatics.h"
#include "DRPlayerCharacter.h"
#include "DRAbility.h"
#include "DRGameMode.h"

void ADREnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ADREnemyAIController::StartRequestAction()
{
	check(!GetWorldTimerManager().IsTimerActive(RequestActionTimer));
	UE_LOG(LogTemp, Warning, TEXT("Start: %f"), FPlatformTime::Seconds());
	GetWorldTimerManager().SetTimer(RequestActionTimer, this, &ADREnemyAIController::RequestAction,
	                                mRequestActionDelay);
}

void ADREnemyAIController::RequestAction()
{
	GetWorldTimerManager().ClearTimer(RequestActionTimer); // This shouldn't be necessary, timer has run out.
	UE_LOG(LogTemp, Warning, TEXT("End: %f"), FPlatformTime::Seconds());

	TArray<ADRPlayerCharacter*> allPlayerUnits = mGameMode->GetAllPlayerUnits();
	ADRPlayerCharacter* closestPlayerUnit;
	float closestDistance;
	UDRGameplayStatics::GetClosestDRCharacterInList(mOwner, allPlayerUnits, closestPlayerUnit, closestDistance);

	if (TryUseAbility()) return;
	if (TryBasicAttack(closestPlayerUnit)) return;
	if (TryMoveTo(closestPlayerUnit)) return;
	mGameMode->EndTurn();
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

bool ADREnemyAIController::TryBasicAttack(ADRCharacter* target)
{
	UDRAbility_BasicAttack* basicAttack = mOwner->GetAbilityComponent()->GetBasicAttack();
	if (basicAttack->CanAffordCast() && basicAttack->IsInRange(target))
	{
		mOwner->BasicAttack(target);
		return true;
	}
	return false;
}

bool ADREnemyAIController::TryMoveTo(ADRCharacter* target)
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
