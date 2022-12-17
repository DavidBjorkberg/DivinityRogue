// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRHealthBar : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateHealthbar(int maxHealth, int currentHealth);

};
