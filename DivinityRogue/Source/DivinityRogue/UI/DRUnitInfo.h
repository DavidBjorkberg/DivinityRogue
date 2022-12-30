// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "DRHealthBar.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "UObject/Object.h"
#include "DRUnitInfo.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRUnitInfo : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(ADRCharacter* character);
protected:
	UPROPERTY(meta=(BindWidget))
	UImage* mImage;
	UPROPERTY(meta=(BindWidget))
	UImage* mBorder;
	UPROPERTY(meta=(BindWidget))
	UDRHealthBar* mHealthbar;
	UPROPERTY(BlueprintReadOnly)
	ADRCharacter* mCharacter;
private:
	UFUNCTION()
	void OnHealthChange(int newHealth);
};
