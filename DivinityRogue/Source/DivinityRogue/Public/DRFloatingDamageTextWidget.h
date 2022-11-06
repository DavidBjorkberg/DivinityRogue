// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DRFloatingDamageTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRFloatingDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* mDamageText;
};
