// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbilityComponent.h"
#include "DRAIController.h"
#include "DRCharacterAnimationComponent.h"
#include "DRMovementComponent.h"
#include "DRStatsComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Pawn.h"
#include "DRCharacter.generated.h"

class UDRAbility;
class UDRAbility_BasicAttack;

UENUM()
enum class ETeam :uint8
{
	PLAYER,
	ENEMY,
	NEUTRAL
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUnitDied, ADRCharacter*, deadUnit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnStart);

UCLASS()
class DIVINITYROGUE_API ADRCharacter : public APawn
{
	GENERATED_BODY()

public:
	ADRCharacter();
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;
	void Heal(int healAmount);
	void ModifyEnergy(int amount);
	void OrderMoveToLocation(FVector targetLoc);
	void OrderMoveToActor(AActor* targetActor);
	void EndTurnIfOutOfActionPoints();
	UFUNCTION()
	void OnTurnStart();

	//Getters
	UFUNCTION(BlueprintCallable,BlueprintPure)
	USkeletalMeshComponent* GetSkeletalMeshComp() const { return mSkeletalMeshComponent; }
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UBoxComponent* GetHitBox() const { return mHitBox; }
	UFUNCTION(BlueprintCallable,BlueprintPure)
	ETeam GetTeam() const { return mTeam; }
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UDRCharacterAnimationComponent* GetAnimationComponent() const { return mAnimationComponent; }
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UDRStatsComponent* GetStatsComponent() const { return mStatsComponent; }
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UDRAbilityComponent* GetAbilityComponent() const { return mAbilityComponent; }
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UDRMovementComponent* GetMovementComp() const { return mMovementComponent; }
	//Getters - End

	UPROPERTY(BlueprintAssignable)
	FUnitDied mOnUnitDied;
	UPROPERTY(BlueprintAssignable)
	FTurnStart mOnTurnStart;
protected:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* mRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRMovementComponent* mMovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* mSkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRCharacterAnimationComponent* mAnimationComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRStatsComponent* mStatsComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRAbilityComponent* mAbilityComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* mHitBox;
	//Components - End

	ETeam mTeam;
private:
	void Died();
	UPROPERTY()
	ADRAIController* mController;
	UPROPERTY()
	ADRGameMode* mGameMode;
};
