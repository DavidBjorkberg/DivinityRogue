// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRScreenUI.h"
#include "DRAbilityTargetComponent.h"
#include "DRGameOverUI.h"
#include "DRPlayerController.h"
#include "DRFloatingDamageText.h"
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
	void ShowGameOverScreen();
	void ShowNextMapSelect();
	void SpawnFloatingDamageText(AActor* damagedActor, int damage, bool isHeal);
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDRScreenUI> mScreenUIClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDRGameOverUI> mGameOverUIClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADRFloatingDamageText> mFloatingDamageTextClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> mNextMapSelectClass;
private:
	void DrawAbilityRangeCircle();
	void DrawAbilityCostText();
	void DrawFloatingDamageTexts();
	UFUNCTION()
	void OnMouseHoverStateChanged(EMouseHoverState newState);

	UPROPERTY()
	TArray<ADRFloatingDamageText*> mFloatingDamageTexts;
 	UPROPERTY()
	UDRScreenUI* mScreenUI;
	UPROPERTY()
	UDRRoundSystem* mRoundSystem;
	UPROPERTY()
	ADRGameMode* mGameMode;
	int mAttackCost;
	bool mIsTargeting;
};
