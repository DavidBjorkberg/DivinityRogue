// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRTurnQueue.h"
#include "DRRoundSystem.generated.h"

class ADRGameMode;
class ADRCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FNewturn, ADRCharacter*, previousCharacter, ADRCharacter*, newCharacter);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNewRound);

UCLASS()
class DIVINITYROGUE_API UDRRoundSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	UFUNCTION(BlueprintCallable)
	void EndTurn();
	UFUNCTION(BlueprintCallable)
	bool IsPlayersTurn();
	ADRCharacter* GetCharacterInPlay() const { return mCharacterInPlay; }
	void RemoveFromTurnQueue(ADRCharacter* character);
	UDRTurnQueue* GetTurnQueue() const { return mTurnQueue; }

	UPROPERTY(BlueprintAssignable)
	FNewturn mOnNewTurn;
	UPROPERTY(BlueprintAssignable)
	FNewRound mOnNewRound;
protected:
	UPROPERTY(BlueprintReadOnly)
	ADRCharacter* mCharacterInPlay;
private:
	UPROPERTY()
	APlayerController* mPlayerController;
	UPROPERTY()
	ADRGameMode* mGameMode;
	UPROPERTY()
	UDRTurnQueue* mTurnQueue;
	UFUNCTION()
	void StartMatch();
	void StartTurn();
	void StartRound();
	void EndRound();
};
