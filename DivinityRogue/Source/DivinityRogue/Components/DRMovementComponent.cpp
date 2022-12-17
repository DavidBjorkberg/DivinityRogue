// Fill out your copyright notice in the Description page of Project Settings.


#include "DRMovementComponent.h"

#include "DRAIController.h"
#include "DRCharacter.h"

void UDRMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	mOwner = Cast<ADRCharacter>(GetOwner());
	mOwner->mOnTurnStart.AddDynamic(this, &UDRMovementComponent::OnTurnStart);
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
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

int UDRMovementComponent::GetEnergyCostToMouse()
{
	const float characterMovement = mOwner->GetStatsComponent()->GetStats().mMovement;
	float pathLength = mGameMode->GetPathToMouse()->GetPathLength();
	pathLength -= mDistanceLeftUntilEnergyCost;
	int energyCost = FMath::CeilToInt(pathLength / characterMovement);
	return energyCost;
}

void UDRMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	if(OldVelocity.Size() > 0)
	{
		SetDesiredRotation(OldVelocity.GetSafeNormal2D().Rotation());
		FVector moveVec = OldVelocity * DeltaSeconds;
		mDistanceLeftUntilEnergyCost -= moveVec.Length();
		if (mDistanceLeftUntilEnergyCost <= 0)
		{
			mOwner->FindComponentByClass<UDRStatsComponent>()->ModifyEnergy(-1);
			mOwner->EndTurnIfOutOfActionPoints();
			mDistanceLeftUntilEnergyCost = mOwner->GetStatsComponent()->GetStats().mMovement;
		}

	}
}

void UDRMovementComponent::OnTurnStart()
{
	mDistanceLeftUntilEnergyCost = mOwner->GetStatsComponent()->GetStats().mMovement;
}
