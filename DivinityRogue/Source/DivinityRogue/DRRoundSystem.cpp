// Fill out your copyright notice in the Description page of Project Settings.


#include "DRRoundSystem.h"

#include "DREnemyAIController.h"
#include "DRGameplayStatics.h"
#include "DRHUD.h"
#include "DRPlayerCharacter.h"

bool UDRRoundSystem::ShouldCreateSubsystem(UObject* Outer) const
{
	// not sure what this is but it's named "/Temp/Untitled" and only has the RF_Transactional object flag
	// indicates that we're in the editor (and not in PIE either)
	if (Outer->GetFlags() == RF_Transactional)
		return false;

	const UWorld* world = Outer->GetWorld();
	return world && (world->WorldType == EWorldType::Type::PIE || world->WorldType == EWorldType::Type::Game)
	&& world->GetName() != "MainMenu";
}

void UDRRoundSystem::OnWorldBeginPlay(UWorld& InWorld)
{
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mPlayerController = GetWorld()->GetFirstPlayerController();
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UDRRoundSystem::StartMatch);
}

void UDRRoundSystem::StartMatch()
{
	StartRound();
}

void UDRRoundSystem::EndTurn()
{
	if (mGameMode->IsGameOver())
	{
		GetWorld()->GetFirstPlayerController()->GetHUD<ADRHUD>()->ShowGameOverScreen();
	}
	else
	{
		StartTurn();
	}
}

bool UDRRoundSystem::IsPlayersTurn()
{
	return Cast<ADRPlayerCharacter>(mCharacterInPlay) != nullptr;
}

void UDRRoundSystem::RemoveFromTurnQueue(ADRCharacter* character)
{
	mTurnQueue.Remove(character);
}

void UDRRoundSystem::StartTurn()
{
	if (mTurnQueue.Num() == 0)
	{
		EndRound();
		return;
	}
	if (mTurnQueue.Num() == 0) return;

	ADRCharacter* previousCharacter = mCharacterInPlay;
	mCharacterInPlay = mTurnQueue[0];
	mTurnQueue.RemoveAt(0);

	mOnNewTurn.Broadcast(previousCharacter, mCharacterInPlay);
	mCharacterInPlay->mOnTurnStart.Broadcast();
	mGameMode->SetGameplayState(EGameplayState::PlanningPath);

	if (ADREnemyAIController* enemyController = Cast<ADREnemyAIController>(mCharacterInPlay->GetController()))
	{
		mPlayerController->DisableInput(mPlayerController);
		enemyController->StartRequestAction();
	}
	else
	{
		mPlayerController->EnableInput(mPlayerController);
	}
}

void UDRRoundSystem::FillTurnQueue()
{
	TArray<AActor*> allActors;
	UDRGameplayStatics::GetAllActorsOfClass(GetWorld(), ADRCharacter::StaticClass(), allActors);
	TArray<ADRCharacter*> allCharacters;
	for (AActor* actor : allActors)
	{
		allCharacters.Add(Cast<ADRCharacter>(actor));
	}
	mTurnQueue = allCharacters;
	mTurnQueue.Sort([](const ADRCharacter& a, const ADRCharacter& b)
	{
		return a.GetStatsComponent()->GetStats().mSpeed > b.GetStatsComponent()->GetStats().mSpeed;
	});
}

void UDRRoundSystem::StartRound()
{
	mOnNewRound.Broadcast();
	FillTurnQueue();
	StartTurn();
}

void UDRRoundSystem::EndRound()
{
	StartRound();
}