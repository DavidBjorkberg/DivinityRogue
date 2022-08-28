// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "DRGameMode.h"
#include "GameFramework/HUD.h"
#include "DRHUD.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API ADRHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	void StartTargeting();
	void StopTargeting();
	void ShowHoverPanel(ADRCharacter* hoveredCharacter);
	void HideHoverPanel();
	bool IsShowingHoverPanel() const { return mShowHoverPanel; }
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDRScreenUI> mScreenUIBP;
private:
	UFUNCTION()
	void OnGameplayStateChanged(EGameplayState oldState, EGameplayState newState);
	UPROPERTY()
	UDRScreenUI* mScreenUI;
	UPROPERTY()
	ADRGameMode* mGameMode;
	bool mIsTargeting;
	bool mShowHoverPanel;
};
