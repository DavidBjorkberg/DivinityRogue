// Fill out your copyright notice in the Description page of Project Settings.


#include "DREnemyAIController.h"

#include "DRGameplayStatics.h"
#include "DRPlayerCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
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
	for (UDRAbility* ability : mOwner->GetCharacterStats().mAbilities)
	{
		if (ability->TrySetRandomTargets())
		{
			mOwner->PlayAttackAnimation(ability);
			return;
		}
	}
	TArray<ADRPlayerCharacter*> allPlayerUnits = mGameMode->GetAllPlayerUnits();
	ADRPlayerCharacter* closestPlayerUnit;
	float closestDistance;
	UDRGameplayStatics::GetClosestDRCharacterInList(mOwner, allPlayerUnits, closestPlayerUnit, closestDistance);

	if (closestDistance > mAdjacentToActorThreshold)
	{
		OrderMoveToActor(closestPlayerUnit);
	}
	else
	{
		mGameMode->EndTurn();
	}
}

void ADREnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (Result.IsSuccess() && mOwner->GetCharacterStats().mCurrentActionPoints > 0)
	{
		StartRequestAction();
	}
}

void ADREnemyAIController::OnFinishedAttack()
{
	Super::OnFinishedAttack();
	if (mOwner->GetCharacterStats().mCurrentActionPoints > 0)
	{
		StartRequestAction();
	}
}
