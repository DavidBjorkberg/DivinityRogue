// Fill out your copyright notice in the Description page of Project Settings.


#include "DivinityRogue/Public/DRMovementComponent.h"

void UDRMovementComponent::RequestPathMove(const FVector& MoveVelocity)
{
	Super::RequestPathMove(MoveVelocity);
}

void UDRMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	if (MoveVelocity.SizeSquared() < KINDA_SMALL_NUMBER)
	{
		return;
	}
	FHitResult result;
	SafeMoveUpdatedComponent(MoveVelocity.GetSafeNormal2D(), GetOwner()->GetActorRotation(), false, result);
}

bool UDRMovementComponent::CanStartPathFollowing() const
{
	return Super::CanStartPathFollowing();
}

