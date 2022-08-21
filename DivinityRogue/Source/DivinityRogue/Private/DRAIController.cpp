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
}
void ADRAIController::OrderMoveToActor(AActor* targetActor)
{
	MoveToActor(targetActor,5,false);
}
// void ADRAIController::MoveToLocation(FVector targetLoc)
// {
// 	mOwner->SetAnimState(EAnimState::MOVE);
// 	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,targetLoc);
// }
//
// void ADRAIController::MoveToActor(AActor* targetActor)
// {
// 	mOwner->SetAnimState(EAnimState::MOVE);
// 	Moveto(this,targetActor);
// 	//UAIBlueprintHelperLibrary::SimpleMoveToActor(this,targetActor);
// }


void ADRAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (Result.IsSuccess())
	{
		mOwner->SetAnimState(EAnimState::IDLE);
		mOwner->ConsumeActionPoints(1);
	}
}
