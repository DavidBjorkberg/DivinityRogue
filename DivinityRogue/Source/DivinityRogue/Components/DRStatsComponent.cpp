#include "DRStatsComponent.h"

#include "DRCharacter.h"


UDRStatsComponent::UDRStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDRStatsComponent::ModifyEnergy(int difference)
{
	mStats.mCurrentActionPoints = FMath::Clamp(mStats.mCurrentActionPoints + difference, 0, mStats.mMaxActionPoints);
	mOnEnergyChange.Broadcast(mStats.mCurrentActionPoints);
}

void UDRStatsComponent::ApplyStats(UDRCharacterTemplate* charTemplate)
{
	mStats.mSpeed = charTemplate->Speed;
	mStats.mMaxActionPoints = charTemplate->MaxActionPoints;
	mStats.mStartActionPoints = charTemplate->StartActionPoints;
	mStats.mCurrentActionPoints = charTemplate->StartActionPoints;
	mStats.mActionPointsPerTurn = charTemplate->ActionPointsPerTurn;
	mStats.mMovement = charTemplate->Movement;
	mStats.mMovementSpeed = charTemplate->MovementSpeed;
}
