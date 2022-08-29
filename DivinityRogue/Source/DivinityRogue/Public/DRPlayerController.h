// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "DRGameMode.h"
#include "DRHUD.h"
#include "DRMovementSpline.h"
#include "GameFramework/PlayerController.h"
#include "DRPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCharacterUnderCursorChanged,ADRCharacter*, previousCharacter, ADRCharacter*, characterUnderCursor);
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
	ADRCharacter* GetCharacterUnderCursor() const {return mCharacterUnderCursor;}
	FCharacterUnderCursorChanged mOnCharacterUnderCursorChanged;
protected:
	virtual void SetupInputComponent() override;
	UFUNCTION()
	void OnLeftMouseClick();
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADRMovementSpline> mMovementSplineBP;
	UPROPERTY(EditDefaultsOnly)
	UUserWidget* mDefaultCursorWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> mAttackCursorWidget;
private:
	UFUNCTION()
	void OnGameplayStateChanged(EGameplayState oldState, EGameplayState newState);
	UFUNCTION()
	void OnNewTurn(ADRCharacter* previousCharacter, ADRCharacter* newCharacter);
	UFUNCTION()
	void OnCharacterUnderCursorChanged(ADRCharacter* previousCharacter, ADRCharacter* characterUnderCursor);
	void UseTargetedAbility(ADRCharacter* target);
	void HoverPanelCheck();
	void UpdateCharacterUnderCursor();
	UPROPERTY()
	ADRGameMode* mGameMode;
	UPROPERTY()
	ADRHUD* mHUD;
	UPROPERTY()
	ADRMovementSpline* mMovementSpline;
	UPROPERTY()
	ADRCharacter* mCharacterUnderCursor;
};
