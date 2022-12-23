// Fill out your copyright notice in the Description page of Project Settings.


#include "DRAbilityTargetComponent.h"

#include "DRStatsComponent.h"

UDRAbilityTargetComponent::UDRAbilityTargetComponent()
{
	UPrimitiveComponent::SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UPrimitiveComponent::SetCollisionProfileName("Pawn");

	SetCanEverAffectNavigation(false);
	SetReceivesDecals(false);
}


void UDRAbilityTargetComponent::SetHighlight(bool enabled)
{
	mHighlightMesh->SetRenderCustomDepth(enabled);
}

void UDRAbilityTargetComponent::TakeDamage(float DamageAmount, AActor* DamageCauser)
{
	const FDamageEvent damageEvent;
	GetOwner()->TakeDamage(DamageAmount, damageEvent, DamageCauser->GetInstigatorController(), DamageCauser);
}

void UDRAbilityTargetComponent::ModifyEnergy(int difference)
{
	if (UDRStatsComponent* statsComp = GetOwner()->FindComponentByClass<UDRStatsComponent>())
	{
		check(statsComp->GetStats().mCurrentActionPoints + difference >= 0);
		statsComp->ModifyEnergy(difference);
	}
}

void UDRAbilityTargetComponent::TeleportTo(FVector targetLocation)
{
	GetOwner()->SetActorLocation(targetLocation + FVector(0,0,GetOwner()->GetSimpleCollisionHalfHeight()));
}

void UDRAbilityTargetComponent::SetHighlightMesh(UPrimitiveComponent* mesh)
{
	mHighlightMesh = mesh;
	mHighlightMesh->CustomDepthStencilValue = 1;
}
