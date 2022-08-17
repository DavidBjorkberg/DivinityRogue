// Fill out your copyright notice in the Description page of Project Settings.


#include "DRGameMode.h"

#include "DRGameplayStatics.h"
#include "DRPlayerCharacter.h"

ADRGameMode::ADRGameMode()
{
	
}

void ADRGameMode::BeginPlay()
{
	Super::BeginPlay();
	AActor* playerChar = UDRGameplayStatics::GetActorOfClass(GetWorld(),ADRPlayerCharacter::StaticClass());
	mCharacterInPlay = Cast<ADRPlayerCharacter>(playerChar);
}


void ADRGameMode::SetTargetLocation(FVector targetLoc)
{
	mCharacterInPlay->SetTargetLocation(targetLoc);
}
