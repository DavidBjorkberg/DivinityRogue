// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "DRMovementSpline.h"
#include "GameFramework/PlayerController.h"
#include "DRPlayerController.generated.h"

class ADRHUD;

UENUM()
enum EMouseHoverState
{
	NoCharacter,
	AllyCharacter,
	EnemyCharacter,
	EnemyCharacterInBasicAttackRange
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCharacterUnderCursorChanged, ADRCharacter*, previousCharacter,
                                             ADRCharacter*, characterUnderCursor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeftMouseDown);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseHoverStateChanged, EMouseHoverState, newState);

UCLASS()
class DIVINITYROGUE_API ADRPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADRPlayerController();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintPure)
	ADRCharacter* GetCharacterUnderCursor() const { return mCharacterUnderCursor; }

	UFUNCTION(BlueprintPure)
	EMouseHoverState GetMouseHoverState() const { return mMouseHoverState; }

	FCharacterUnderCursorChanged mOnCharacterUnderCursorChanged;
	FLeftMouseDown mOnLeftMouseDown;
	FOnMouseHoverStateChanged mOnMouseHoverStateChanged;
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
	void UpdateCursor();
	void UpdateMouseHoverState(ADRCharacter* characterUnderCursor);
	void UpdateCharacterUnderCursor();
	UPROPERTY()
	ADRGameMode* mGameMode;
	UPROPERTY()
	ADRHUD* mHUD;
	UPROPERTY()
	ADRMovementSpline* mMovementSpline;
	UPROPERTY()
	ADRCharacter* mCharacterUnderCursor;
	EMouseHoverState mMouseHoverState;
};
