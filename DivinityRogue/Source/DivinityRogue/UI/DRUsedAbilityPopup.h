// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DRUsedAbilityPopup.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRUsedAbilityPopup : public UUserWidget
{
	GENERATED_BODY()
public:
	void Show(ADRCharacter* character, UDRAbility* ability,float duration);
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* mCharacterText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* mAbilityText;
};
