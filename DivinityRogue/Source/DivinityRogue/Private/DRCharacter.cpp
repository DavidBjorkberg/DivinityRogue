// Fill out your copyright notice in the Description page of Project Settings.


#include "DRCharacter.h"

// Sets default values
ADRCharacter::ADRCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

