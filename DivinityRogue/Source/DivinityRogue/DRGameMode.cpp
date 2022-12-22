// Fill out your copyright notice in the Description page of Project Settings.


#include "DRGameMode.h"

#include "DRAbility.h"
#include "DREnemyAIController.h"
#include "DREnemyCharacter.h"
#include "DRGameplayStatics.h"
#include "DRHUD.h"
#include "DRPlayerCharacter.h"
#include "DRPlayerController.h"
#include "DRSaveGameManager.h"
#include "NavigationSystem.h"
#include "GameFramework/PlayerStart.h"

ADRGameMode::ADRGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADRGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnPlayerCharacters();

	TArray<ADRCharacter*> allCharacters;
	UDRGameplayStatics::FindAllActors<ADRCharacter>(GetWorld(), allCharacters);
	for (ADRCharacter* character : allCharacters)
	{
		character->mOnUnitDied.AddDynamic(this, &ADRGameMode::OnUnitDied);
	}

	mPlayerController = Cast<ADRPlayerController>(GetWorld()->GetFirstPlayerController());
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ADRGameMode::StartMatch);
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
	if (index >= 0 && !abilities[index]->IsOnCooldown() && abilities[index]->CanAffordCast())
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

TArray<UDRAbilityTargetComponent*> ADRGameMode::GetAllPlayerAbilityTargets()
{
	TArray<UDRAbilityTargetComponent*> allAbilityTargets;
	TArray<UDRAbilityTargetComponent*> returnList;
	UDRGameplayStatics::FindAllComponents<UDRAbilityTargetComponent>(GetWorld(), allAbilityTargets);
	for (UDRAbilityTargetComponent* abilityTarget : allAbilityTargets)
	{
		if (abilityTarget->GetTeam() == ETeam::PLAYER)
		{
			returnList.Add(abilityTarget);
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

void ADRGameMode::SpawnPlayerCharacters()
{
	UDRGameInstance* GI = GetGameInstance<UDRGameInstance>();
	if (GI->mPlayerCharacters.Num() == 0)
	{
		TArray<ADRPlayerCharacter*> playerCharacters;
		UDRGameplayStatics::FindAllActors<ADRPlayerCharacter>(GetWorld(), playerCharacters);
		GI->InitializePlayerCharactersWithOverrides(playerCharacters);
		for (int i = playerCharacters.Num() - 1; i >= 0; i--)
		{
			playerCharacters[i]->Destroy();
		}
	}

	TArray<APlayerStart*> playerSpawnpoints;
	UDRGameplayStatics::FindAllActors<APlayerStart>(GetWorld(), playerSpawnpoints);
	for (int i = 0; i < GI->mPlayerCharacters.Num(); i++)
	{
		ADRCharacter* spawnedChar = GetWorld()->SpawnActor<ADRPlayerCharacter>(mPlayerCharacterClass);
		spawnedChar->SetActorLocation(playerSpawnpoints[i]->GetActorLocation());
		spawnedChar->Initialize(GI->mPlayerCharacters[i]);
	}
}

void ADRGameMode::StartMatch()
{
	StartRound();
}

void ADRGameMode::EndTurn()
{
	if (IsGameOver())
	{
		GetWorld()->GetFirstPlayerController()->GetHUD<ADRHUD>()->ShowGameOverScreen(mCurrentRound);
	}
	else
	{
		StartTurn();
	}
}

bool ADRGameMode::IsPlayersTurn()
{
	return Cast<ADRPlayerCharacter>(mCharacterInPlay) != nullptr;
}

void ADRGameMode::StartTurn()
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
	SetGameplayState(EGameplayState::PlanningPath);

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
	StartTurn();
}

void ADRGameMode::EndRound()
{
	mCurrentRound++;
	StartRound();
}

void ADRGameMode::OnUnitDied(ADRCharacter* deadUnit)
{
	mTurnQueue.Remove(deadUnit);
	TArray<ADREnemyCharacter*> allEnemyCharacters;
	TArray<ADRPlayerCharacter*> allPlayerCharacters;
	UDRGameplayStatics::FindAllActors<ADREnemyCharacter>(GetWorld(), allEnemyCharacters);
	UDRGameplayStatics::FindAllActors<ADRPlayerCharacter>(GetWorld(), allPlayerCharacters);

	if (allPlayerCharacters.Num() == 0)
	{
		SetGameOver(true);
	}
	else if(allEnemyCharacters.Num() == 0)
	{
		GetWorld()->GetFirstPlayerController()->GetHUD<ADRHUD>()->ShowNextMapSelect();
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
		pathEnd = mPlayerController->GetAbilityTargetUnderCursor()->GetOwner()->GetActorLocation();
	}
	else
	{
		pathEnd = UDRGameplayStatics::GetHitResultUnderCursor(GetWorld(), ECC_WorldStatic).Location;
	}
	mPathToMouse = UNavigationSystemV1::FindPathToLocationSynchronously(
		GetWorld(), pathStart, pathEnd, mCharacterInPlay);
}
