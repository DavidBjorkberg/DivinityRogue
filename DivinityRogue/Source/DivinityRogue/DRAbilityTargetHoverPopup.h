// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbilityTargetComponent.h"
#include "DRHealthBar.h"
#include "DRHealthComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DRAbilityTargetHoverPopup.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRAbilityTargetHoverPopup : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Show(UDRAbilityTargetComponent* target);
	UFUNCTION(BlueprintCallable)
	void Hide();
protected:
	UPROPERTY(meta = (BindWidget))
	UDRHealthBar* mHealthBar;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* mNameText;
private:
	UFUNCTION()
	void OnHealthChanged(int newHealth);
	UPROPERTY()
	UDRAbilityTargetComponent* mTarget;
	UPROPERTY()
	UDRHealthComponent* mTargetHealthComponent;
};
