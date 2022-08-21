// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRCharacter.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DRUseAbilityNotify.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRUseAbilityNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	void SetParameters(UDRAbility* ability, ADRCharacter* user, ADRCharacter* target);
private:
	UPROPERTY()
	UDRAbility* mAbility;
	UPROPERTY()
	ADRCharacter* mUser;
	UPROPERTY()
	ADRCharacter* mTarget;
};
