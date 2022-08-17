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
	StartMatch();
}


void ADRGameMode::SetTargetLocation(FVector targetLoc)
{
	mCharacterInPlay->SetTargetLocation(targetLoc);
}

void ADRGameMode::OnActionCompleted()
{
	EndTurn();
}

void ADRGameMode::StartMatch()
{
	StartTurn();
}

void ADRGameMode::EndTurn()
{
	StartTurn();
}

void ADRGameMode::StartTurn()
{
	if (mTurnQueue.Num() == 0)
	{
		FillTurnQueue();
	}
	mCharacterInPlay = mTurnQueue[0];
	mTurnQueue.RemoveAt(0);
}

void ADRGameMode::FillTurnQueue()
{
	TArray<AActor*> allActors;
	UDRGameplayStatics::GetAllActorsOfClass(GetWorld(), ADRCharacter::StaticClass(), allActors);
	TArray<ADRCharacter*> allCharacters;
	for (AActor* actor : allActors)
	{
		allCharacters.Add(Cast<ADRCharacter>(actor));
	}
	mTurnQueue = allCharacters;
	Algo::SortBy(mTurnQueue, &ADRCharacter::GetSpeed);
}
