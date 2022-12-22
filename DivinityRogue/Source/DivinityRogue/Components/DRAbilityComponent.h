// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAbility_BasicAttack.h"
#include "DRCharacterTemplate.h"
#include "Components/ActorComponent.h"
#include "DRAbilityComponent.generated.h"


UCLASS()
class DIVINITYROGUE_API UDRAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDRAbilityComponent();

	void ApplyTemplate(UDRCharacterTemplate* charTemplate);
	UFUNCTION(BlueprintPure)
	TArray<UDRAbility*> GetAbilities() const { return mAbilities; }

	UDRAbility_BasicAttack* GetBasicAttack() const { return mBasicAttack; }
protected:
	UPROPERTY(VisibleAnywhere)
	TArray<UDRAbility*> mAbilities;
	UPROPERTY(VisibleAnywhere)
	UDRAbility_BasicAttack* mBasicAttack;
};
