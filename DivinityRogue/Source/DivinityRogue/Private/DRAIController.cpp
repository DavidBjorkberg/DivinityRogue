// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAIController.h"

#include "DRGameMode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ADRAIController::ADRAIController()
{
}

void ADRAIController::BeginPlay()
{
	Super::BeginPlay();
	mOwner = Cast<ADRCharacter>(GetPawn());
}
void ADRAIController::MoveToLocation(FVector targetLoc)
{
	mOwner->SetAnimState(EAnimState::MOVE);
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,targetLoc);
}

void ADRAIController::MoveToActor(AActor* targetActor)
{
	mOwner->SetAnimState(EAnimState::MOVE);
	UAIBlueprintHelperLibrary::SimpleMoveToActor(this,targetActor);
}

void ADRAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (Result.IsSuccess())
	{
		mOwner->SetAnimState(EAnimState::IDLE);
		GetWorld()->GetAuthGameMode<ADRGameMode>()->OnActionCompleted();
	}
}
