// Fill out your copyright notice in the Description page of Project Settings.


#include "DRNexus.h"

#include "DRGameMode.h"

// Sets default values
ADRNexus::ADRNexus()
{
	mRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(mRoot);
	mStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	mStaticMeshComponent->SetupAttachment(mRoot);
	mAbilityTargetComponent = CreateDefaultSubobject<UDRAbilityTargetComponent>("DRAbilityTargetComponent");
	mAbilityTargetComponent->SetupAttachment(mRoot);
	mAbilityTargetComponent->SetHighlightMesh(mStaticMeshComponent);
	mHealthComponent = CreateDefaultSubobject<UDRHealthComponent>("DRHealthComponent");
	mHealthComponent->mOnDied.AddDynamic(this, &ADRNexus::OnDeath);
	mAbilityTargetComponent->SetTeam(ETeam::PLAYER);
}

float ADRNexus::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	mHealthComponent->ModifyHealth(-DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ADRNexus::OnDeath()
{
	GetWorld()->GetAuthGameMode<ADRGameMode>()->SetGameOver(true);
}


