// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbility_GroundTarget.h"

#include "DRGameplayStatics.h"
#include "NavigationSystem.h"
#include "Components/DecalComponent.h"


void UDRAbility_GroundTarget::Tick(float DeltaTime)
{
	if (mIsSelected)
	{
		FHitResult mouseGroundHitResult;
		if (UDRGameplayStatics::GetGroundHitResultUnderCursor(mWorld, mouseGroundHitResult, false))
		{
			mDecalActorInst->SetActorLocation(mouseGroundHitResult.Location);
			mDecalActorInst->SetActorRotation((-mouseGroundHitResult.Normal).Rotation());
		}
		if (IsOnValidArea())
		{
			SetDecalMaterial(mDecalMaterial);
		}
		else
		{
			SetDecalMaterial(mInvalidDecalMaterial);
		}
	}
}

bool UDRAbility_GroundTarget::TrySetRandomTargets()
{
	FNavLocation randomLocation;

	if (UNavigationSystemV1::GetCurrent(GetWorld())->GetRandomPointInNavigableRadius(
		mOwner->GetActorLocation(), mAbilityInfo.mRange, randomLocation))
	{
		mTargetLocation = randomLocation.Location;
		return true;
	}
	return false;
}

void UDRAbility_GroundTarget::ClearSelection()
{
	mTargetLocation = FVector::ZeroVector;
}

void UDRAbility_GroundTarget::OnAbilitySelected()
{
	Super::OnAbilitySelected();
	mDecalActorInst = GetWorld()->SpawnActor<ADRCircleDecal>(mDecalActor);
	SetDecalMaterial(mDecalMaterial);
	mDecalActorInst->SetRadius(mRadius);
}

void UDRAbility_GroundTarget::OnAbilityDeselected()
{
	Super::OnAbilityDeselected();
	mDecalActorInst->Destroy();
}

bool UDRAbility_GroundTarget::IsOnValidArea()
{
	FHitResult groundUnderCursorHitResult;
	UDRGameplayStatics::GetGroundHitResultUnderCursor(mWorld, groundUnderCursorHitResult, false);
	return IsInRange(groundUnderCursorHitResult.Location);
}

bool UDRAbility_GroundTarget::IsValidTarget(UDRAbilityTargetComponent* target)
{
	return target != nullptr && IsTargetCorrectTeam(target);
}

void UDRAbility_GroundTarget::SetDecalMaterial(UMaterialInterface* newMaterial)
{
	mDecalActorInst->GetDecalComponent()->SetDecalMaterial(newMaterial);
}
