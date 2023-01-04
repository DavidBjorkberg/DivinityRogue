// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRPartyUnitInfo.h"
#include "DRTurnOrderUnitInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "DRPartyUI.generated.h"

class ADRCharacter;
/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRPartyUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* mUnitInfos;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDRPartyUnitInfo> mUnitInfoClass;
private:
	UFUNCTION()
	void AddCharacter(ADRCharacter* characterToAdd);
};
