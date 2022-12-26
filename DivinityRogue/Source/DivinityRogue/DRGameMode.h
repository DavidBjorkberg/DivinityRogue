// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbilityTargetComponent.h"
#include "DRRoundSystem.h"
#include "GameFramework/GameModeBase.h"
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
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADRPlayerCharacter> mPlayerCharacterClass;
private:
	void SpawnPlayerCharacters();
	UFUNCTION()
	void OnUnitDied(ADRCharacter* deadUnit);
	UPROPERTY()
	UDRRoundSystem* mRoundSystem;
	UPROPERTY()
	UDRAbility* mSelectedAbility;
	EGameplayState mCurrentGameplayState;
	bool mGameOver;
};
