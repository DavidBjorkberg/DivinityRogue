// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbilityTargetComponent.h"
#include "DRCharacterTemplate.h"
#include "DRRoundSystem.h"
#include "GameFramework/GameModeBase.h"
#include "Sound/SoundCue.h"
#include "DRGameMode.generated.h"

class ADRPlayerController;
class UDRAbility;
class ADRPlayerCharacter;
class ADREnemyCharacter;
class ADRCharacter;
UENUM()
enum class EGameplayState : uint8
{
	PlanningPath,
	WalkingPath,
	SelectingTarget,
	PerformingAbility,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameplayStateChange, EGameplayState, oldState, EGameplayState, newState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSelectedAbilityChanged, UDRAbility*, ability);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterSpawned, ADRCharacter*, spawnedCharacter);

UCLASS()
class DIVINITYROGUE_API ADRGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADRGameMode();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintPure)
	bool IsInGameplayState(EGameplayState state) const { return state == mCurrentGameplayState; }
	void SetGameplayState(EGameplayState newState);

	bool IsGameOver() const { return mGameOver; }
	void SetGameOver(bool gameOver) { mGameOver = gameOver; }

	UFUNCTION(BlueprintCallable)
	void TrySelectAbility(UDRAbility* ability);
	UDRAbility* GetSelectedAbility() const { return mSelectedAbility; }

	TArray<UDRAbilityTargetComponent*> GetAllPlayerAbilityTargets();

	UPROPERTY(BlueprintAssignable)
	FGameplayStateChange mOnGameplayStateChanged;

	UPROPERTY(BlueprintAssignable)
	FSelectedAbilityChanged mOnSelectedAbilityChanged;
	UPROPERTY(BlueprintAssignable)
	FCharacterSpawned mOnCharacterSpawned;
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADRCharacter> mPlayerCharacterClass;
	UPROPERTY(EditDefaultsOnly)
	USoundCue* mBackgroundMusicCue;
	UPROPERTY(EditDefaultsOnly)
	float mGameOverDelay;
private:
	void InitializePlayerCharacters();
	void InitializeEnemyCharacters();
	void SpawnCharacter(UDRCharacterTemplate* charTemplate, FVector location,FRotator rotation, ETeam team);
	UFUNCTION()
	void OnUnitDied(ADRCharacter* deadUnit);
	UPROPERTY()
	UDRRoundSystem* mRoundSystem;
	UPROPERTY()
	UDRAbility* mSelectedAbility;
	EGameplayState mCurrentGameplayState;
	bool mGameOver;
};
