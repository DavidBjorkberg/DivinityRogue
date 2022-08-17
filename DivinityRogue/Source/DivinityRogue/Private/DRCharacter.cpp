// Fill out your copyright notice in the Description page of Project Settings.


#include "DRCharacter.h"

ADRCharacter::ADRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	mMovementComponent = CreateDefaultSubobject<UDRMovementComponent>("MovementComponent");
	mSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SetRootComponent(mSkeletalMeshComponent);

}

void ADRCharacter::SetTargetLocation(FVector targetLoc)
{
	mController->SetTargetLocation(targetLoc);
}

void ADRCharacter::BeginPlay()
{
	Super::BeginPlay();
	mController = Cast<ADRAIController>(GetController() );
}
