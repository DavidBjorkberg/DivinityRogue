// Fill out your copyright notice in the Description page of Project Settings.


#include "DRCharacter.h"

ADRCharacter::ADRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(mRoot);
	mMovementComponent = CreateDefaultSubobject<UDRMovementComponent>("MovementComponent");
	mSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	mSkeletalMeshComponent->SetupAttachment(mRoot);
}

void ADRCharacter::SetTargetLocation(FVector targetLoc)
{
	mController->SetTargetLocation(targetLoc);
}

void ADRCharacter::BeginPlay()
{
	Super::BeginPlay();
	mCurrentHealth = mMaxHealth;
	mController = Cast<ADRAIController>(GetController());
	for (TSubclassOf<ADRAbility> ability : mAbilities)
	{
		ADRAbility* spawnedAbility = GetWorld()->SpawnActor<ADRAbility>(ability);
		mSpawnedAbilities.Add(spawnedAbility);
	}
}

bool ADRCharacter::TryUseAbility(ADRAbility* ability, ADRCharacter* target)
{
	return ability->TryUse(this,target);
}

float ADRCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                               AActor* DamageCauser)
{
	mCurrentHealth = FMath::Max(mCurrentHealth - DamageAmount, 0);
	if(mCurrentHealth <= 0)
	{
		Died();
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ADRCharacter::Died()
{
	UE_LOG(LogTemp,Warning,TEXT("Died"));
}
