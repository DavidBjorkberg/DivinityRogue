#include "DRStatsComponent.h"

#include "DRCharacter.h"


UDRStatsComponent::UDRStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDRStatsComponent::ModifyEnergy(int difference)
{
	mStats.mCurrentEnergy = FMath::Clamp(mStats.mCurrentEnergy + difference, 0, mStats.mMaxEnergy);
	mOnEnergyChange.Broadcast(mStats.mCurrentEnergy);
}

void UDRStatsComponent::ApplyTemplate(UDRCharacterTemplate* charTemplate)
{
	mStats.mInitiative = charTemplate->Speed;
	mStats.mMaxEnergy = charTemplate->MaxEnergy;
	mStats.mEnergyPerTurn = charTemplate->EnergyPerTurn;
	mStats.mMovement = charTemplate->Movement;
	mStats.mMovementSpeed = charTemplate->MovementSpeed;
}
