// Fill out your copyright notice in the Description page of Project Settings.


#include "DRGameMode.h"

#include "DRAbility.h"
#include "DREnemyAIController.h"
#include "DREnemyCharacter.h"
#include "DRGameplayStatics.h"
#include "DRPlayerCharacter.h"
#include "DRPlayerController.h"
#include "NavigationSystem.h"

ADRGameMode::ADRGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
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
	mPlayerController = Cast<ADRPlayerController>(GetWorld()->GetFirstPlayerController());
}

void ADRGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (IsInGameplayState(EGameplayState::PlanningPath))
	{
		FindPathToMouse();
	}
}

void ADRGameMode::SetGameplayState(EGameplayState newState)
{
	mOnGameplayStateChanged.Broadcast(mCurrentGameplayState, newState);
	mCurrentGameplayState = newState;
	UE_LOG(LogTemp, Warning, TEXT("Changed to state: %s"), *UEnum::GetValueAsString( newState));
}

void ADRGameMode::TrySelectAbility(int index)
{
	TArray<UDRAbility*> abilities = mCharacterInPlay->GetAbilityComponent()->GetAbilities();
	if (index >= 0 && !abilities[index]->IsOnCooldown())
	{
		mSelectedAbility = abilities[index];
		SetGameplayState(EGameplayState::SelectingTarget);
	}
	else
	{
		mSelectedAbility = nullptr;
		SetGameplayState(EGameplayState::PlanningPath);
	}
	mOnSelectedAbilityChanged.Broadcast(mSelectedAbility);
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

UNavigationPath* ADRGameMode::GetPathToMouse()
{
	if (mPathToMouse == nullptr)
	{
		FindPathToMouse();
	}
	return mPathToMouse;
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

void ADRGameMode::SpawnCharacter(TSubclassOf<ADRCharacter> charToSpawn, FVector spawnPos)
{
	ADRCharacter* spawnedChar = GetWorld()->SpawnActor<ADRCharacter>(charToSpawn);
	check(spawnedChar)
	spawnedChar->SetActorLocation(spawnPos);
	spawnedChar->mOnUnitDied.AddDynamic(this, &ADRGameMode::OnUnitDied);
	mALlCharacters.Add(spawnedChar);
}

void ADRGameMode::StartTurn()
{
	if (mTurnQueue.Num() == 0)
	{
		StartRound();
	}
	if (mTurnQueue.Num() == 0) return;

	ADRCharacter* previousCharacter = mCharacterInPlay;
	mCharacterInPlay = mTurnQueue[0];
	mTurnQueue.RemoveAt(0);

	mOnNewTurn.Broadcast(previousCharacter, mCharacterInPlay);
	mCharacterInPlay->mOnTurnStart.Broadcast();
	SetGameplayState(EGameplayState::PlanningPath);
	if (mCharacterInPlay->GetTeam() == ETeam::PLAYER)
	{
		mPlayerController->EnableInput(mPlayerController);
	}
	else
	{
		mPlayerController->DisableInput(mPlayerController);
		ADREnemyAIController* enemyController = Cast<ADREnemyAIController>(mCharacterInPlay->GetController());
		enemyController->StartRequestAction();
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
	mTurnQueue.Sort([](const ADRCharacter& a, const ADRCharacter& b)
	{
		return a.GetStatsComponent()->GetStats().mSpeed > b.GetStatsComponent()->GetStats().mSpeed;
	});
}

void ADRGameMode::StartRound()
{
	mOnNewRound.Broadcast();
	FillTurnQueue();
}

void ADRGameMode::OnUnitDied(ADRCharacter* deadUnit)
{
	mALlCharacters.Remove(deadUnit);
	mTurnQueue.Remove(deadUnit);
	if (GetAllPlayerUnits().Num() == 0 || GetAllEnemyUnits().Num() == 0)
	{
		UDRGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
	}
}

void ADRGameMode::FindPathToMouse()
{
	if (mCharacterInPlay == nullptr)
	{
		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		mPathToMouse = NewObject<UNavigationPath>(NavSys);
		return;
	}
	FVector pathStart = mCharacterInPlay->GetActorLocation();
	FVector pathEnd;

	if (mPlayerController->GetMouseHoverState() == EMouseHoverState::EnemyCharacterInBasicAttackRange)
	{
		pathEnd = mPlayerController->GetCharacterUnderCursor()->GetActorLocation();
	}
	else
	{
		pathEnd = UDRGameplayStatics::GetHitResultUnderCursor(GetWorld(), ECC_WorldStatic).Location;
	}
	mPathToMouse = UNavigationSystemV1::FindPathToLocationSynchronously(
		GetWorld(), pathStart, pathEnd, mCharacterInPlay);
}
