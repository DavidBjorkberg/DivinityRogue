// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAIController.h"
#include "DRGameMode.h"
#include "DRHealthBar.h"
#include "DRMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Pawn.h"
#include "DRCharacter.generated.h"

UENUM()
enum class EAnimState :uint8
{
	IDLE,
	ATTACK,
	MOVE,
};

UENUM()
enum class ETeam :uint8
{
	PLAYER,
	ENEMY,
	NEUTRAL
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUnitDied, ADRCharacter*, deadUnit);

UCLASS()
class DIVINITYROGUE_API ADRCharacter : public APawn
{
	GENERATED_BODY()

public:
	ADRCharacter();
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;
	virtual void OnFinishedAttack();
	void OrderMoveToLocation(FVector targetLoc);
	bool TryUseAbility(UDRAbility* ability, ADRCharacter* target);
	void OnTurnStart();
	void ConsumeActionPoints(int amount);
	void EndTurnIfOutOfActionPoints();

	UFUNCTION(BlueprintCallable)
	bool IsInAnimState(EAnimState state) { return state == mCurrentAnimState; }

	void PlayAttackAnimation(UDRAbility* ability, ADRCharacter* target);
	void PlayIdleAnimation();
	void PlayRunAnimation();

	UFUNCTION(BlueprintCallable)
	UDRAbility* GetAbility(int index) { return mSpawnedAbilities[index]; }

	UFUNCTION(BlueprintCallable)
	TArray<UDRAbility*> GetAbilities() { return mSpawnedAbilities; }

	USkeletalMeshComponent* GetSkeletalMeshComp() const { return mSkeletalMeshComponent; }
	int GetSpeed() const { return mSpeed; };
	int GetCurrentActionPoints() const { return mCurrentActionPoints; }
	ETeam GetTeam() const { return mTeam; }
	FUnitDied mOnUnitDied;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* mRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRMovementComponent* mMovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* mSkeletalMeshComponent;
	UPROPERTY(EditAnywhere, Category = "DRCharacter")
	int mSpeed = 5;
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	int mMaxHealth = 10;
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	int mMaxActionPoints = 2;
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	int mStartActionPoints = 2;
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	int mActionPointsPerTurn = 2;
	UPROPERTY(EditDefaultsOnly, Category = "DRCharacter")
	TArray<TSubclassOf<UDRAbility>> mAbilities;
	int mCurrentActionPoints;
	ETeam mTeam;
private:
	void Died();
	void SetAnimState(EAnimState newState) { mCurrentAnimState = newState; }
	int mCurrentHealth;
	UPROPERTY()
	UAnimSequenceBase* mAttackAnimation;
	UPROPERTY()
	ADRAIController* mController;
	EAnimState mCurrentAnimState;
	UPROPERTY()
	TArray<UDRAbility*> mSpawnedAbilities;
	UPROPERTY()
	UWidgetComponent* mHealthBarWidget;
	UPROPERTY()
	UDRHealthBar* mHealthBar;
	UPROPERTY()
	ADRGameMode* mGameMode;
};
