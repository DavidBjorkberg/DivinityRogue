// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAIController.h"
#include "DRMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Pawn.h"
#include "DRCharacter.generated.h"

class UDRAbility;
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

USTRUCT(BlueprintType)
struct FCharacterBaseStats
{
	GENERATED_BODY()
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
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	int mMovementSpeed = 6;
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	int mMovement = 2;
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	FString mName;
	UPROPERTY(EditDefaultsOnly, Category = "DRCharacter")
	TArray<TSubclassOf<UDRAbility>> mAbilities;
};

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, DisplayName="Name")
	FString mName;
	UPROPERTY(BlueprintReadOnly, DisplayName="Max Health")
	int mMaxHealth;
	UPROPERTY(BlueprintReadOnly, DisplayName="Current Health")
	int mCurrentHealth ;
	UPROPERTY(BlueprintReadOnly, DisplayName="Speed")
	int mSpeed;
	UPROPERTY(BlueprintReadOnly, DisplayName="Movement Speed")
	int mMovementSpeed;
	UPROPERTY(BlueprintReadOnly, DisplayName="Movement")
	int mMovement;
	UPROPERTY(BlueprintReadOnly, DisplayName="Max Energy")
	int mMaxActionPoints;
	UPROPERTY(BlueprintReadOnly, DisplayName="Current Energy")
	int mCurrentActionPoints;
	UPROPERTY(BlueprintReadOnly, DisplayName="Start Energy")
	int mStartActionPoints;
	UPROPERTY(BlueprintReadOnly, DisplayName="Energy per turn")
	int mActionPointsPerTurn;
	UPROPERTY(BlueprintReadOnly, DisplayName="Abilities")
	TArray<UDRAbility*> mAbilities;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUnitDied, ADRCharacter*, deadUnit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChange, int, newHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnergyChange, int, newEnergy);
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
	virtual void Tick(float DeltaSeconds) override;
	void OrderMoveToLocation(FVector targetLoc);
	void OrderMoveToActor(AActor* targetActor);
	bool TryUseAbility(UDRAbility* ability, ADRCharacter* target);
	void ModifyEnergy(int amount);
	void EndTurnIfOutOfActionPoints();
	UFUNCTION()
	void OnTurnStart();

	UFUNCTION(BlueprintCallable)
	bool IsInAnimState(EAnimState state) { return state == mCurrentAnimState; }

	void PlayAttackAnimation(UDRAbility* ability, ADRCharacter* target);
	void PlayIdleAnimation();
	void PlayRunAnimation();

	USkeletalMeshComponent* GetSkeletalMeshComp() const { return mSkeletalMeshComponent; }
	ETeam GetTeam() const { return mTeam; }
	UFUNCTION(BlueprintCallable)
	FCharacterStats GetCharacterStats() const { return mStats; }


	float mDistanceLeftUntilEnergyCost;

	UPROPERTY(BlueprintAssignable)
	FUnitDied mOnUnitDied;
	UPROPERTY(BlueprintAssignable)
	FHealthChange mOnHealthChange;
	UPROPERTY(BlueprintAssignable)
	FEnergyChange mOnEnergyChange;
	UPROPERTY(BlueprintAssignable)
	FTurnStart mOnTurnStart;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* mRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRMovementComponent* mMovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* mSkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* mHitBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCharacterBaseStats mBaseStats;
	UPROPERTY(BlueprintReadOnly)
	FCharacterStats mStats;
	ETeam mTeam;
private:
	void Died();
	void SetAnimState(EAnimState newState) {mCurrentAnimState = newState; }
	void ApplyBaseStats();
	UPROPERTY()
	UAnimSequenceBase* mAttackAnimation;
	UPROPERTY()
	ADRAIController* mController;
	EAnimState mCurrentAnimState;

	UPROPERTY()
	ADRGameMode* mGameMode;
};
