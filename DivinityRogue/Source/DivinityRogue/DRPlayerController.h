// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "DRMovementSpline.h"
#include "DRAbilityTargetComponent.h"
#include "GameFramework/PlayerController.h"
#include "DRPlayerController.generated.h"

class ADRHUD;

UENUM()
enum EMouseHoverState
{
	NoCharacter,
	AllyCharacter,
	EnemyCharacter,
	EnemyCharacterInBasicAttackRange,
	HoverUI,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCharacterUnderCursorChanged,
                                             UDRAbilityTargetComponent*, previousSelectableComp,
                                             UDRAbilityTargetComponent*, newSelectableComp);

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
	UDRAbilityTargetComponent* GetAbilityTargetUnderCursor() const { return mSelectableUnderCursor; }

	//Returns the path to the mouse. Truncated to the length the current character can walk.
	UNavigationPath* FindTruncatedPathToMouse();

	UFUNCTION(BlueprintPure)
	EMouseHoverState GetMouseHoverState() const { return mMouseHoverState; }

	UFUNCTION(BlueprintCallable)
	void SetMouseHoverState(EMouseHoverState newState) { mMouseHoverState = newState; }

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
	UFUNCTION(BlueprintCallable)
	UNavigationPath* GetPathToMouse();
	UFUNCTION()
	void OnGameplayStateChanged(EGameplayState oldState, EGameplayState newState);
	UFUNCTION()
	void OnNewTurn(ADRCharacter* previousCharacter, ADRCharacter* newCharacter);
	UFUNCTION()
	void OnSelectableUnderCursorChanged(UDRAbilityTargetComponent* previousSelectableComp,
	                                    UDRAbilityTargetComponent* newSelectableComp);
	void UpdateCursor();
	void UpdateMouseHoverState(UDRAbilityTargetComponent* abilityTargetUnderCursor);
	void UpdateCharacterUnderCursor();

	UPROPERTY()
	ADRGameMode* mGameMode;
	UPROPERTY()
	UDRRoundSystem* mRoundSystem;
	UPROPERTY()
	ADRHUD* mHUD;
	UPROPERTY()
	ADRMovementSpline* mMovementSpline;
	UPROPERTY()
	UDRAbilityTargetComponent* mSelectableUnderCursor;
	EMouseHoverState mMouseHoverState;
};
