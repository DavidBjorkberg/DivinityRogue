#include "DRStatsComponent.h"


UDRStatsComponent::UDRStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDRStatsComponent::UpdateHealth(int difference)
{
	mStats.mCurrentHealth = FMath::Clamp(mStats.mCurrentHealth + difference, 0, mStats.mMaxHealth);
	mOnHealthChange.Broadcast(mStats.mCurrentHealth);
}

void UDRStatsComponent::UpdateEnergy(int difference)
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
	mStats.mMaxHealth = mBaseStats.mMaxHealth;
	mStats.mCurrentHealth = mBaseStats.mMaxHealth;
	mStats.mSpeed = mBaseStats.mSpeed;
	mStats.mMaxActionPoints = mBaseStats.mMaxActionPoints;
	mStats.mStartActionPoints = mBaseStats.mStartActionPoints;
	mStats.mCurrentActionPoints = mBaseStats.mStartActionPoints;
	mStats.mActionPointsPerTurn = mBaseStats.mActionPointsPerTurn;
	mStats.mMovement = mBaseStats.mMovement;
	mStats.mMovementSpeed = mBaseStats.mMovementSpeed;
}
