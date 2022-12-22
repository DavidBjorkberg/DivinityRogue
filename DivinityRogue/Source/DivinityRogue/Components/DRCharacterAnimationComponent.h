// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacterAnimInstance.h"
#include "Components/ActorComponent.h"
#include "DRCharacterAnimationComponent.generated.h"

class UDRAbility;
UENUM()
enum class EAnimState :uint8
{
	IDLE,
	ATTACK,
	MOVE,
};

UCLASS()
class DIVINITYROGUE_API UDRCharacterAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDRCharacterAnimationComponent();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	bool IsInAnimState(EAnimState state) { return state == mCurrentAnimState; }

	void SetAnimInstance(TSubclassOf<UDRCharacterAnimInstance> animInstanceClass);
	void PlayAttackAnimation(UDRAbility* ability);
	void PlayIdleAnimation();
	void PlayRunAnimation();
private:
	void SetAnimState(EAnimState newState) { mCurrentAnimState = newState; }
	UPROPERTY()
	UAnimSequenceBase* mAttackAnimation;
	EAnimState mCurrentAnimState;
};
