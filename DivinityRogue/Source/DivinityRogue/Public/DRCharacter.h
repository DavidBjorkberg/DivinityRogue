// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAIController.h"
#include "DRMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "DRCharacter.generated.h"

UENUM()
enum class EAnimState :uint8
{
	IDLE,
	ATTACK,
	MOVE,
};

UCLASS()
class DIVINITYROGUE_API ADRCharacter : public APawn
{
	GENERATED_BODY()

public:
	ADRCharacter();
	void SetTargetLocation(FVector targetLoc);
	virtual void BeginPlay() override;
	int GetSpeed() const { return mSpeed; };
	UFUNCTION(BlueprintCallable)
	bool IsInAnimState(EAnimState state) { return state == mCurrentAnimState; }
	void SetAnimState(EAnimState newState) { mCurrentAnimState = newState; };
	ADRAbility* GetAbility(int index) { return mSpawnedAbilities[index]; };
	bool TryUseAbility(ADRAbility* ability, ADRCharacter* target);
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* mRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRMovementComponent* mMovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* mSkeletalMeshComponent;
	UPROPERTY(EditAnywhere, Category = "DRCharacter")
	int mSpeed;
	UPROPERTY(EditAnyWhere, Category = "DRCharacter")
	int mMaxHealth;
	UPROPERTY(EditDefaultsOnly, Category = "DRCharacter")
	TArray<TSubclassOf<ADRAbility>> mAbilities;
private:
	void Died();
	int mCurrentHealth;
	UPROPERTY()
	ADRAIController* mController;
	EAnimState mCurrentAnimState;
	UPROPERTY()
	TArray<ADRAbility*> mSpawnedAbilities;
};
