// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbilityComponent.h"
#include "DRAIController.h"
#include "DRCharacterAnimationComponent.h"
#include "DRHealthComponent.h"
#include "DRMovementComponent.h"
#include "DRStatsComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "DRCharacter.generated.h"

class UDRAbility;
class UDRAbility_BasicAttack;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUnitDied, ADRCharacter*, deadUnit);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUsedAbility, UDRAbility*, ability);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPreUsedAbility, UDRAbility*, ability);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnStart);

UCLASS()
class DIVINITYROGUE_API ADRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADRCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;
	void Heal(int healAmount);
	void OrderMoveToLocation(FVector targetLoc);
	void OrderMoveToActor(UDRAbilityTargetComponent* target);
	void OrderAttackMoveToActor(UDRAbilityTargetComponent* target);
	void BasicAttack(UDRAbilityTargetComponent* target);
	void EndTurnIfOutOfActionPoints();
	void UseAbility(UDRAbility* ability);
	UFUNCTION()
	void OnTurnStart();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UDRCharacterAnimationComponent* GetAnimationComponent() const { return mAnimationComponent; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UDRStatsComponent* GetStatsComponent() const { return mStatsComponent; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UDRAbilityComponent* GetAbilityComponent() const { return mAbilityComponent; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UDRHealthComponent* GetHealthComponent() const { return mHealthComponent; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UDRMovementComponent* GetDRMovementComponent();
	//Getters - End

	UPROPERTY(BlueprintAssignable)
	FUnitDied mOnUnitDied;
	UPROPERTY(BlueprintAssignable)
	FTurnStart mOnTurnStart;
	UPROPERTY(BlueprintAssignable)
	FUsedAbility mOnUsedAbility;
	UPROPERTY(BlueprintAssignable)
	FPreUsedAbility mOnPreUsedAbility;
protected:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRCharacterAnimationComponent* mAnimationComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRStatsComponent* mStatsComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRHealthComponent* mHealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRAbilityComponent* mAbilityComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRAbilityTargetComponent* mAbilityTargetComponent;
	//Components - End


private:
	UFUNCTION()
	void Died();
	UPROPERTY()
	ADRAIController* mController;
	UPROPERTY()
	ADRGameMode* mGameMode;
};
