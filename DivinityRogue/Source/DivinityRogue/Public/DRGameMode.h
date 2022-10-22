// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRScreenUI.h"
#include "NavigationPath.h"
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FNewturn, ADRCharacter*, previousCharacter, ADRCharacter*, newCharacter);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSelectedAbilityChanged, UDRAbility*, ability);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNewRound);

UCLASS()
class DIVINITYROGUE_API ADRGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADRGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void EndTurn();
	bool IsPlayersTurn();
	UFUNCTION(BlueprintCallable)
	void SpawnCharacter(TSubclassOf<ADRCharacter> charToSpawn, FVector spawnPos);
	//Set
	void SetGameplayState(EGameplayState newState);
	UFUNCTION(BlueprintCallable)
	void SetSelectedAbility(int index);
	//

	//Get
	UFUNCTION(BlueprintPure)
	bool IsInGameplayState(EGameplayState state) { return state == mCurrentGameplayState; }

	UDRAbility* GetSelectedAbility() const { return mSelectedAbility; }
	ADRCharacter* GetCharacterInPlay() const { return mCharacterInPlay; }
	TArray<ADREnemyCharacter*> GetAllEnemyUnits();
	TArray<ADRPlayerCharacter*> GetAllPlayerUnits();
	UFUNCTION(BlueprintCallable)
	UNavigationPath* GetPathToMouse();
	ADRPlayerController* GetPlayerController() const { return mPlayerController; }
	//

	bool IsMouseOnValidEnemyForBasicAttack();
	UPROPERTY(BlueprintAssignable)
	FGameplayStateChange mOnGameplayStateChanged;
	UPROPERTY(BlueprintAssignable)
	FNewturn mOnNewTurn;
	UPROPERTY(BlueprintAssignable)
	FNewRound mOnNewRound;
	UPROPERTY(BlueprintAssignable)
	FSelectedAbilityChanged mOnSelectedAbilityChanged;
protected:
	UPROPERTY(BlueprintReadOnly)
	ADRCharacter* mCharacterInPlay;
	UPROPERTY()
	TArray<ADRCharacter*> mTurnQueue;
private:
	UFUNCTION()
	void StartMatch();
	void StartTurn();
	void FillTurnQueue();
	void StartRound();
	UFUNCTION()
	void OnUnitDied(ADRCharacter* deadUnit);
	void FindPathToMouse();
	UPROPERTY()
	UNavigationPath* mPathToMouse;
	UPROPERTY()
	TArray<ADRCharacter*> mALlCharacters;
	UPROPERTY()
	UDRAbility* mSelectedAbility;
	UPROPERTY()
	ADRPlayerController* mPlayerController;
	EGameplayState mCurrentGameplayState;
};
