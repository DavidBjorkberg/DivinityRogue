// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRScreenUI.h"
#include "DRAbilityTargetComponent.h"
#include "DRPlayerController.h"
#include "GameFramework/HUD.h"

#include "DRHUD.generated.h"


enum class EGameplayState : uint8;
class ADRGameMode;
class ADRCharacter;
UCLASS()
class DIVINITYROGUE_API ADRHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	void ShowHoverPanel(UDRAbilityTargetComponent* selectableComp);
	void HideHoverPanel();
	void ShowGameOverScreen(int nrOfRoundsSurvived);
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDRScreenUI> mScreenUIClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> mGameOverUIClass;
private:
	void DrawAbilityRangeCircle();
	void DrawAbilityCostText();
	UFUNCTION()
	void OnMouseHoverStateChanged(EMouseHoverState newState);
	UPROPERTY()
	UDRScreenUI* mScreenUI;
	UPROPERTY()
	ADRGameMode* mGameMode;
	int mAttackCost;
	bool mIsTargeting;
};
