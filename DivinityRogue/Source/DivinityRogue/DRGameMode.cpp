// Fill out your copyright notice in the Description page of Project Settings.


#include "DRGameMode.h"

#include "DRAbility.h"
#include "DREnemyAIController.h"
#include "DRGameplayStatics.h"
#include "DRHUD.h"
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

	mRoundSystem = GetWorld()->GetSubsystem<UDRRoundSystem>();
	InitializePlayerCharacters();
	InitializeEnemyCharacters();

	TArray<ADRCharacter*> allCharacters;
	UDRGameplayStatics::FindAllActors<ADRCharacter>(GetWorld(), allCharacters);
	for (ADRCharacter* character : allCharacters)
	{
		character->mOnUnitDied.AddDynamic(this, &ADRGameMode::OnUnitDied);
	}
}

void ADRGameMode::SetGameplayState(EGameplayState newState)
{
	mOnGameplayStateChanged.Broadcast(mCurrentGameplayState, newState);
	mCurrentGameplayState = newState;
	UE_LOG(LogTemp, Warning, TEXT("Changed to state: %s"), *UEnum::GetValueAsString( newState));
}

void ADRGameMode::TrySelectAbility(UDRAbility* ability)
{
	if (ability && !ability->IsOnCooldown() && ability->CanAffordCast())
	{
		mSelectedAbility = ability;
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


void ADRGameMode::InitializePlayerCharacters()
{
	UDRGameInstance* GI = GetGameInstance<UDRGameInstance>();
	TArray<ADRCharacter*> playerCharacters;
	UDRGameplayStatics::GetAllPlayerCharacters(GetWorld(), playerCharacters);
	if (GI->mPlayerCharacters.Num() == 0)
	{
		GI->InitializePlayerCharactersWithOverrides(playerCharacters);
	}
	for (int i = playerCharacters.Num() - 1; i >= 0; i--)
	{
		playerCharacters[i]->Destroy();
	}

	TArray<APlayerStart*> playerSpawnpoints;
	UDRGameplayStatics::FindAllActors<APlayerStart>(GetWorld(), playerSpawnpoints);
	for (int i = 0; i < GI->mPlayerCharacters.Num(); i++)
	{
		ADRCharacter* spawnedChar = GetWorld()->SpawnActor<ADRCharacter>(mPlayerCharacterClass);
		spawnedChar->SetActorLocation(playerSpawnpoints[i]->GetActorLocation());
		spawnedChar->Initialize(GI->mPlayerCharacters[i], ETeam::PLAYER);
	}
}

void ADRGameMode::InitializeEnemyCharacters()
{
	TArray<ADRCharacter*> enemyCharacters;
	UDRGameplayStatics::GetAllEnemyCharacters(GetWorld(), enemyCharacters);
	for (ADRCharacter* enemyChar : enemyCharacters)
	{
		UDRCharacterTemplate* charTemplate = NewObject<UDRCharacterTemplate>(enemyChar, enemyChar->mCharacterTemplateOverride);
		charTemplate->CurrentHealth = charTemplate->MaxHealth;
		enemyChar->Initialize(charTemplate,ETeam::ENEMY);
	}
}


void ADRGameMode::OnUnitDied(ADRCharacter* deadUnit)
{
	mRoundSystem->RemoveFromTurnQueue(deadUnit);
	TArray<ADRCharacter*> allEnemyCharacters;
	TArray<ADRCharacter*> allPlayerCharacters;
	UDRGameplayStatics::GetAllPlayerCharacters(GetWorld(), allPlayerCharacters);
	UDRGameplayStatics::GetAllEnemyCharacters(GetWorld(), allEnemyCharacters);

	if (allPlayerCharacters.Num() == 0)
	{
		SetGameOver(true);
	}
	else if (allEnemyCharacters.Num() == 0)
	{
		GetWorld()->GetFirstPlayerController()->GetHUD<ADRHUD>()->HideBattleUI();
		GetWorld()->GetFirstPlayerController()->GetHUD<ADRHUD>()->ShowSelectRewardScreen();
	}
}
