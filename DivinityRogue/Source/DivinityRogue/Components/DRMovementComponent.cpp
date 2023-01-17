// Fill out your copyright notice in the Description page of Project Settings.


#include "DRMovementComponent.h"

#include "DRAIController.h"
#include "DRCharacter.h"
#include "DRPlayerController.h"
#include "NavigationPath.h"

void UDRMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	mOwner = Cast<ADRCharacter>(GetOwner());
	mOwner->mOnTurnStart.AddDynamic(this, &UDRMovementComponent::OnTurnStart);
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mPlayerController = GetWorld()->GetFirstPlayerController<ADRPlayerController>();
}

void UDRMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int UDRMovementComponent::GetEnergyCostToMouse()
{
	const float characterMovement = mOwner->GetStatsComponent()->GetStats().mMovement;
	float pathLength = GetPathLengthToMouse();
	pathLength -= mDistanceLeftUntilEnergyCost;
	int energyCost = FMath::CeilToInt(pathLength / characterMovement);
	return energyCost;
}

float UDRMovementComponent::GetWalkableDistance()
{
	const float characterMovement = mOwner->GetStatsComponent()->GetStats().mMovement;
	int currentEnergy = mOwner->GetStatsComponent()->GetStats().mCurrentEnergy;
	float walkableDistance = mDistanceLeftUntilEnergyCost + characterMovement * (currentEnergy - 1);
	return walkableDistance;
}

float UDRMovementComponent::GetPathLengthToMouse()
{
	UNavigationPath* path = mPlayerController->FindTruncatedPathToMouse(); 
	float distance2D = 0;
	for (int i = 0; i < path->PathPoints.Num() - 1; i++)
	{
		if (path->PathPoints[i].Z != path->PathPoints[i + 1].Z)
			continue;
		
		distance2D += FVector::Dist2D(path->PathPoints[i], path->PathPoints[i + 1]);
	}

	return distance2D;
}

void UDRMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	if (OldVelocity.Size2D() > 0)
	{
		SetDesiredRotation(OldVelocity.GetSafeNormal2D().Rotation());
		float distance = FVector::Dist2D(GetOwner()->GetActorLocation(),OldLocation);
		mDistanceLeftUntilEnergyCost -= distance;
		distanceTravelled += distance;
		if (mDistanceLeftUntilEnergyCost <= 0)
		{
			mOwner->FindComponentByClass<UDRStatsComponent>()->ModifyEnergy(-1);
			mOwner->EndTurnIfOutOfActionPoints();
			mDistanceLeftUntilEnergyCost = mOwner->GetStatsComponent()->GetStats().mMovement;
		}
		
		if (!GetOwner()->GetActorRotation().Equals(mDesiredRotation, 10.0f))
		{
			FRotator deltaRotation = mDesiredRotation - GetOwner()->GetActorRotation();
			deltaRotation.Roll = 0;
			deltaRotation.Pitch = 0;
			GetOwner()->AddActorWorldRotation(deltaRotation.GetNormalized() * mRotationRate * DeltaSeconds);
		}
	}
}

void UDRMovementComponent::OnTurnStart()
{
	mDistanceLeftUntilEnergyCost = mOwner->GetStatsComponent()->GetStats().mMovement;
}
