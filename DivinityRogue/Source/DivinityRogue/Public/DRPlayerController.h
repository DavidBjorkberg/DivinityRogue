// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "DRGameMode.h"
#include "DRMovementSpline.h"
#include "GameFramework/PlayerController.h"
#include "DRPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API ADRPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADRPlayerController();
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintCallable)
	void StartTargetAbility(int index);
	virtual void BeginPlay() override;
protected:
	virtual void SetupInputComponent() override;
	UFUNCTION()
	void OnLeftMouseClick();
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ADRMovementSpline> mMovementSplineBP;
private:
	UFUNCTION()
	void OnGameplayStateChanged(EGameplayState oldState, EGameplayState newState);
	void UseTargetedAbility(ADRCharacter* target);
	UPROPERTY()
	ADRGameMode* mGameMode;
	UPROPERTY()
	ADRMovementSpline* mMovementSpline;
	bool mDrawSpline;
	
};
