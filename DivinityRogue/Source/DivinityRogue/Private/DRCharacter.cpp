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
	mController = Cast<ADRAIController>(GetController());
	for(TSubclassOf<ADRAbility> ability : mAbilities)
	{
		ADRAbility* spawnedAbility = GetWorld()->SpawnActor<ADRAbility>(ability);
		mSpawnedAbilities.Add(spawnedAbility);
	}
}

void ADRCharacter::UseAbility(ADRAbility* ability, ADRCharacter* target)
{
	ability->Use(target);
}


