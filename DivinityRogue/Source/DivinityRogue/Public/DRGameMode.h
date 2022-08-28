// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRScreenUI.h"
#include "GameFramework/GameModeBase.h"
#include "DRGameMode.generated.h"

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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FNewturn,ADRCharacter*, previousCharacter, ADRCharacter*, newCharacter);

UCLASS()
class DIVINITYROGUE_API ADRGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADRGameMode();
	virtual void BeginPlay() override;
	void EndTurn();
	ADRCharacter* GetCharacterInPlay() const { return mCharacterInPlay; }
	bool IsPlayersTurn();
	UFUNCTION(BlueprintPure)
	bool IsInGameplayState(EGameplayState state) { return state == mCurrentGameplayState; }
	void SetGameplayState(EGameplayState newState);
	TArray<ADREnemyCharacter*> GetAllEnemyUnits();
	TArray<ADRPlayerCharacter*> GetAllPlayerUnits();
	FGameplayStateChange mOnGameplayStateChanged;
	UPROPERTY(BlueprintAssignable)
	FNewturn mOnNewTurn;
	UPROPERTY()
	UDRAbility* mSelectedAbility;
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
	UFUNCTION()
	void OnUnitDied(ADRCharacter* deadUnit);


	UPROPERTY()
	TArray<ADRCharacter*> mALlCharacters;
	EGameplayState mCurrentGameplayState;
};
