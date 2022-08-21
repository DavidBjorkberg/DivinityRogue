// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRAIController.h"
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


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUnitDied, ADRCharacter*, deadUnit);

UCLASS()
class DIVINITYROGUE_API ADRCharacter : public APawn
{
	GENERATED_BODY()

public:
	ADRCharacter();
	void MoveToLocation(FVector targetLoc);
	virtual void BeginPlay() override;
	int GetSpeed() const { return mSpeed; };
	UFUNCTION(BlueprintCallable)
	bool IsInAnimState(EAnimState state) { return state == mCurrentAnimState; }

	void SetAnimState(EAnimState newState) { mCurrentAnimState = newState; }
	UFUNCTION(BlueprintCallable)
	UDRAbility* GetAbility(int index) { return mSpawnedAbilities[index]; }

	UFUNCTION(BlueprintCallable)
	TArray<UDRAbility*> GetAbilities() { return mSpawnedAbilities; }

	bool TryUseAbility(UDRAbility* ability, ADRCharacter* target);
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;
	USkeletalMeshComponent* GetSkeletalMeshComp() const { return mSkeletalMeshComponent; }
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
	UPROPERTY(EditDefaultsOnly, Category = "DRCharacter")
	TArray<TSubclassOf<UDRAbility>> mAbilities;
private:
	void Died();
	int mCurrentHealth;
	UPROPERTY()
	ADRAIController* mController;
	EAnimState mCurrentAnimState;
	UPROPERTY()
	TArray<UDRAbility*> mSpawnedAbilities;
	UPROPERTY()
	UWidgetComponent* mHealthBarWidget;
	UPROPERTY()
	UDRHealthBar* mHealthBar;
};
