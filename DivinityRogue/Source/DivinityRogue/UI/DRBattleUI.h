// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbilityTargetComponent.h"
#include "DRUsedAbilityPopup.h"
#include "Components/Button.h"
#include "DRBattleUI.generated.h"

enum class EGameplayState : uint8;
class ADRCharacter;
/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRBattleUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UDRBattleUI(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintImplementableEvent)
	void ShowHoverPanel(UDRAbilityTargetComponent* selectableComp);
	UFUNCTION(BlueprintImplementableEvent)
	void HideHoverCharacterPanel();
	void ShowUsedAbilityPopup(ADRCharacter* character, UDRAbility* ability,float duration);
private:
	UFUNCTION()
	void OnGameplayStateChanged(EGameplayState oldState, EGameplayState newState);

	UPROPERTY(meta=(BindWidget))
	UDRUsedAbilityPopup* mUsedAbilityPopup;
	UPROPERTY(meta=(BindWidget))
	UButton* mEndTurnButton;
};
