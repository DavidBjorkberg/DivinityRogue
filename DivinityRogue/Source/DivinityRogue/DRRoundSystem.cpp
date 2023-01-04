// Fill out your copyright notice in the Description page of Project Settings.


#include "DRRoundSystem.h"

#include "DREnemyAIController.h"
#include "DRGameplayStatics.h"
#include "DRHUD.h"

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
	mTurnQueue = NewObject<UDRTurnQueue>(this);
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UDRRoundSystem::StartMatch);
}

void UDRRoundSystem::StartMatch()
{
	StartRound();
}

void UDRRoundSystem::EndTurn()
{
	mCharacterInPlay->mOnTurnEnd.Broadcast();

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
	return mCharacterInPlay && mCharacterInPlay->GetAbilityTargetComponent()->GetTeam() == ETeam::PLAYER;
}

void UDRRoundSystem::RemoveFromTurnQueue(ADRCharacter* character)
{
	mTurnQueue->Remove(character);
}

void UDRRoundSystem::StartTurn()
{
	if (mTurnQueue->IsEmpty())
	{
		EndRound();
		return;
	}
	if (mTurnQueue->IsEmpty()) return;

	ADRCharacter* previousCharacter = mCharacterInPlay;
	mCharacterInPlay = mTurnQueue->GetNext();

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

void UDRRoundSystem::StartRound()
{
	mOnNewRound.Broadcast();
	mTurnQueue->FillQueueFromWorld();
	StartTurn();
}

void UDRRoundSystem::EndRound()
{
	StartRound();
}
