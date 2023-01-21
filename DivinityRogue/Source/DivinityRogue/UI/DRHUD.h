// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRBattleUI.h"
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
	void ShowBattleUI();
	UFUNCTION(BlueprintCallable)
	void HideBattleUI();
	void ShowHoverPanel(UDRAbilityTargetComponent* selectableComp);
	void HideHoverPanel();
	void ShowGameOverScreen();
	UFUNCTION(BlueprintCallable)
	void ShowNextMapSelect();
	void ShowSelectRewardScreen();
	UFUNCTION(BlueprintCallable)
	void HideSelectRewardScreen();
	void SpawnFloatingDamageText(AActor* damagedActor, int damage, bool isHeal);
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDRBattleUI> mScreenUIClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDRGameOverUI> mGameOverUIClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADRFloatingDamageText> mFloatingDamageTextClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> mNextMapSelectClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> mSelectRewardClass;
private:
	void DrawAbilityRangeCircle();
	void DrawActionCostText();
	void DrawPathLengthText();
	void DrawFloatingDamageTexts();
	UPROPERTY()
	TArray<ADRFloatingDamageText*> mFloatingDamageTexts;
 	UPROPERTY()
	UDRBattleUI* mBattleUI;
 	UPROPERTY()
	ADRPlayerController* mPlayerController;
	UPROPERTY()
	UDRRoundSystem* mRoundSystem;
	UPROPERTY()
	ADRGameMode* mGameMode;
	UPROPERTY()
	UUserWidget* mSelectRewardUI;
};
