// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAbility_BasicAttack.h"
#include "Components/ActorComponent.h"
#include "DRAbilityComponent.generated.h"


UCLASS()
class DIVINITYROGUE_API UDRAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDRAbilityComponent();

public:
	UFUNCTION(BlueprintPure)
	TArray<UDRAbility*> GetAbilities() const { return mAbilities; }

	UDRAbility_BasicAttack* GetBasicAttack() const { return mBasicAttack; }
protected:
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, DisplayName="Abilities")
	TArray<UDRAbility*> mAbilities;
	UPROPERTY(BlueprintReadOnly, DisplayName="Basic Attack")
	UDRAbility_BasicAttack* mBasicAttack;

	UPROPERTY(EditDefaultsOnly, Category = "DRCharacter")
	TArray<TSubclassOf<UDRAbility>> mAbilityClasses;
	UPROPERTY(EditDefaultsOnly, Category = "DRCharacter")
	TSubclassOf<UDRAbility_BasicAttack> mBasicAttackClass;
private:
	void SpawnStarterAbilities();
};
