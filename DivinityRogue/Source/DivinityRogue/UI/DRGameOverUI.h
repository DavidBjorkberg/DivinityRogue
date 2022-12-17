// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DRGameOverUI.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRGameOverUI : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetValues(int nrOfRoundsSurvived);
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* mRoundText;
};
