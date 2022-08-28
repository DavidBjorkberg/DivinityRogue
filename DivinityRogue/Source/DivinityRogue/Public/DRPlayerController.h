// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "DRGameMode.h"
#include "DRHUD.h"
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
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void StartTargetAbility(int index);
protected:
	virtual void SetupInputComponent() override;
	UFUNCTION()
	void OnLeftMouseClick();
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADRMovementSpline> mMovementSplineBP;
private:
	UFUNCTION()
	void OnGameplayStateChanged(EGameplayState oldState, EGameplayState newState);
	UFUNCTION()
	void OnNewTurn(ADRCharacter* previousCharacter, ADRCharacter* newCharacter);
	void UseTargetedAbility(ADRCharacter* target);
	void HoverPanelCheck();
	UPROPERTY()
	ADRGameMode* mGameMode;
	UPROPERTY()
	ADRHUD* mHUD;
	UPROPERTY()
	ADRMovementSpline* mMovementSpline;
};
