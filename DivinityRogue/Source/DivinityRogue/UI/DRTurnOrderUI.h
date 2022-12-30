// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "DRUnitInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "DRTurnOrderUI.generated.h"

UCLASS()
class DIVINITYROGUE_API UDRTurnOrderUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* mTurnList;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDRUnitInfo> mUnitInfoClass;
private:
	UFUNCTION()
	void OnCharacterAdded(ADRCharacter* newCharacter, int index);
	UFUNCTION()
	void OnCharacterRemoved(int index);
	void AddUnit(ADRCharacter* character);
};
