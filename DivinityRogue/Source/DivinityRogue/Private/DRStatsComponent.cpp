#include "DRStatsComponent.h"


UDRStatsComponent::UDRStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDRStatsComponent::ModifyEnergy(int difference)
{
	mStats.mCurrentActionPoints = FMath::Clamp(mStats.mCurrentActionPoints + difference, 0, mStats.mMaxActionPoints);
	mOnEnergyChange.Broadcast(mStats.mCurrentActionPoints);
}


// Called when the game starts
void UDRStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	ApplyBaseStats();
}


void UDRStatsComponent::ApplyBaseStats()
{
	mStats.mName = mBaseStats.mName;
	mStats.mSpeed = mBaseStats.mSpeed;
	mStats.mMaxActionPoints = mBaseStats.mMaxActionPoints;
	mStats.mStartActionPoints = mBaseStats.mStartActionPoints;
	mStats.mCurrentActionPoints = mBaseStats.mStartActionPoints;
	mStats.mActionPointsPerTurn = mBaseStats.mActionPointsPerTurn;
	mStats.mMovement = mBaseStats.mMovement;
	mStats.mMovementSpeed = mBaseStats.mMovementSpeed;
}
