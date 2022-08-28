// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRScreenUI.generated.h"

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
	UFUNCTION(BlueprintImplementableEvent)
	void ShowHoverCharacterPanel(ADRCharacter* hoveredCharacter);
	UFUNCTION(BlueprintImplementableEvent)
	void HideHoverCharacterPanel();
};
