// Fill out your copyright notice in the Description page of Project Settings.


#include "DivinityRogue/Public/DRMovementComponent.h"

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
	SetDesiredRotation(MoveVelocity.GetSafeNormal2D().Rotation());
	FHitResult result;
	SafeMoveUpdatedComponent(MoveVelocity.GetSafeNormal2D() * mMovementSpeed, GetOwner()->GetActorRotation(), false,
	                         result);
}

bool UDRMovementComponent::CanStartPathFollowing() const
{
	return Super::CanStartPathFollowing();
}
