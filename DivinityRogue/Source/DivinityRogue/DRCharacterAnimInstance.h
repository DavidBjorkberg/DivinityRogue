// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DRCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* mAttackAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimSequenceBase* mRunAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimSequenceBase* mIdleAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* mTakeDamageAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* mDeathAnimation;
};
