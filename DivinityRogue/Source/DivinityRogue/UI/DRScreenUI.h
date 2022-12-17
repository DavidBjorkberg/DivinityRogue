// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbilityTargetComponent.h"
#include "Components/Button.h"
#include "DRScreenUI.generated.h"

 enum class EGameplayState : uint8;
class ADRCharacter;
/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRScreenUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UDRScreenUI(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintImplementableEvent)
	void ShowHoverPanel(UDRAbilityTargetComponent* selectableComp);
	UFUNCTION(BlueprintImplementableEvent)
	void HideHoverCharacterPanel();

private:
	UFUNCTION()
	void OnGameplayStateChanged(EGameplayState oldState, EGameplayState newState);
	
	UPROPERTY(meta=(BindWidget))
	UButton* mEndTurnButton;
};
