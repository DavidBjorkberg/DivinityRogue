// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "DRPlayerCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "DRGameMode.generated.h"

UENUM()
enum class EGameplayState : uint8
{
	PlanningPath,
	WalkingPath,
	SelectingTarget,
	PerformingAbility,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameplayStateChange, EGameplayState, oldState, EGameplayState, newState);

UCLASS()
class DIVINITYROGUE_API ADRGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADRGameMode();
	virtual void BeginPlay() override;
	void OnActionCompleted();
	ADRCharacter* GetCharacterInPlay() const { return mCharacterInPlay; };
	bool IsPlayersTurn() { return Cast<ADRPlayerCharacter>(mCharacterInPlay) != nullptr; };
	bool IsInGameplayState(EGameplayState state) { return state == mCurrentGameplayState; }
	void SetGameplayState(EGameplayState newState);
	FGameplayStateChange mOnGameplayStateChanged;
	UPROPERTY()
	ADRAbility* mSelectedAbility;
protected:
	UPROPERTY(BlueprintReadOnly)
	ADRCharacter* mCharacterInPlay;
	UPROPERTY()
	TArray<ADRCharacter*> mTurnQueue;

private:
	void StartMatch();
	void EndTurn();
	void StartTurn();
	void FillTurnQueue();

	EGameplayState mCurrentGameplayState;
};
