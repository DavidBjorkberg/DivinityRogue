// Fill out your copyright notice in the Description page of Project Settings.


#include "DREnemyAIController.h"

#include "DRGameplayStatics.h"
#include "DRPlayerCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void ADREnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ADREnemyAIController::StartRequestAction()
{
	check(!GetWorldTimerManager().IsTimerActive(RequestActionTimer));
	GetWorldTimerManager().SetTimer(RequestActionTimer,this,&ADREnemyAIController::RequestAction,mRequestActionDelay);
}

void ADREnemyAIController::RequestAction()
{
	TArray<ADRPlayerCharacter*> allPlayerUnits = mGameMode->GetAllPlayerUnits();

	ADRPlayerCharacter* closestPlayerUnit;
	float closestDistance;
	UDRGameplayStatics::GetClosestDRCharacterInList(GetPawn(), allPlayerUnits, closestPlayerUnit, closestDistance);

	for (UDRAbility* ability : mOwner->GetCharacterStats().mAbilities)
	{
		if (ability->CanCast(mOwner, closestPlayerUnit))
		{
			mOwner->PlayAttackAnimation(ability,closestPlayerUnit);
			return;
		}
	}
	OrderMoveToActor(closestPlayerUnit);
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

