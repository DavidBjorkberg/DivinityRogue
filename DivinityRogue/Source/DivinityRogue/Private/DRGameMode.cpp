// Fill out your copyright notice in the Description page of Project Settings.


#include "DRGameMode.h"

#include "DREnemyAIController.h"
#include "DREnemyCharacter.h"
#include "DRGameplayStatics.h"
#include "DRPlayerCharacter.h"

ADRGameMode::ADRGameMode()
{
}

void ADRGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ADRGameMode::StartMatch);
	UDRGameplayStatics::FindAllActors<ADRCharacter>(GetWorld(), mALlCharacters);
	for (ADRCharacter* character : mALlCharacters)
	{
		character->mOnUnitDied.AddDynamic(this, &ADRGameMode::OnUnitDied);
	}

}

void ADRGameMode::SetGameplayState(EGameplayState newState)
{
	mOnGameplayStateChanged.Broadcast(mCurrentGameplayState, newState);
	mCurrentGameplayState = newState;
}

TArray<ADREnemyCharacter*> ADRGameMode::GetAllEnemyUnits()
{
	TArray<ADREnemyCharacter*> returnList;
	for (ADRCharacter* character : mALlCharacters)
	{
		if (ADREnemyCharacter* enemyUnit = Cast<ADREnemyCharacter>(character))
		{
			returnList.Add(enemyUnit);
		}
	}
	return returnList;
}

TArray<ADRPlayerCharacter*> ADRGameMode::GetAllPlayerUnits()
{
	TArray<ADRPlayerCharacter*> returnList;
	for (ADRCharacter* character : mALlCharacters)
	{
		if (ADRPlayerCharacter* playerUnit = Cast<ADRPlayerCharacter>(character))
		{
			returnList.Add(playerUnit);
		}
	}
	return returnList;
}

void ADRGameMode::StartMatch()
{
	StartTurn();
}

void ADRGameMode::EndTurn()
{
	StartTurn();
}

bool ADRGameMode::IsPlayersTurn()
{
	return Cast<ADRPlayerCharacter>(mCharacterInPlay) != nullptr;
}

void ADRGameMode::StartTurn()
{
	if (mTurnQueue.Num() == 0)
	{
		FillTurnQueue();
	}
	if (mTurnQueue.Num() == 0) return;
	
	ADRCharacter* previousCharacter = mCharacterInPlay;
	mCharacterInPlay = mTurnQueue[0];
	mTurnQueue.RemoveAt(0);
	mOnNewTurn.Broadcast(previousCharacter, mCharacterInPlay);
	mCharacterInPlay->OnTurnStart();
	if (ADREnemyAIController* enemyController = Cast<ADREnemyAIController>(mCharacterInPlay->GetController()))
	{
		enemyController->RequestAction();
	}
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
	mTurnQueue.Sort([](const ADRCharacter& a, const ADRCharacter& b) { return a.GetCharacterStats().mSpeed > b.GetCharacterStats().mSpeed; });
}

void ADRGameMode::OnUnitDied(ADRCharacter* deadUnit)
{
	mALlCharacters.Remove(deadUnit);
	mTurnQueue.Remove(deadUnit);
}
