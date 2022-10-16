// Fill out your copyright notice in the Description page of Project Settings.


#include "DivinityRogue/Public/DRMovementComponent.h"

#include "DRAIController.h"
#include "DRCharacter.h"

void UDRMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	mOwner = Cast<ADRCharacter>(GetOwner());
	mOwner->mOnTurnStart.AddDynamic(this,&UDRMovementComponent::OnTurnStart);
}

void UDRMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!GetOwner()->GetActorRotation().Equals(mDesiredRotation, 10.0f))
	{
		FRotator deltaRotation = mDesiredRotation - GetOwner()->GetActorRotation();
		deltaRotation.Roll = 0;
		deltaRotation.Pitch = 0;
		GetOwner()->AddActorWorldRotation(deltaRotation.GetNormalized() * mRotationRate * DeltaTime);
	}
}

void UDRMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	if (MoveVelocity.SizeSquared() < KINDA_SMALL_NUMBER)
	{
		return;
	}
	SetDesiredRotation(MoveVelocity.GetSafeNormal2D().Rotation());
	FVector moveVec = MoveVelocity.GetSafeNormal() * mOwner->GetStatsComponent()->GetStats().mMovementSpeed;
	mDistanceLeftUntilEnergyCost -= moveVec.Length();

	if(mDistanceLeftUntilEnergyCost <= 0)
	{
		mOwner->ModifyEnergy(-1);
		mOwner->EndTurnIfOutOfActionPoints();
		mDistanceLeftUntilEnergyCost = mOwner->GetStatsComponent()->GetStats().mMovement;
	}	
	FHitResult result;
	SafeMoveUpdatedComponent(moveVec, GetOwner()->GetActorRotation(), false,
	                         result);
}

void UDRMovementComponent::OrderMoveToActor(AActor* targetActor)
{
	Cast<ADRAIController>(Cast<APawn>(GetOwner())->GetController())->OrderMoveToActor(targetActor);
}
void UDRMovementComponent::OnTurnStart()
{
	mDistanceLeftUntilEnergyCost = mOwner->GetStatsComponent()->GetStats().mMovement;
}
