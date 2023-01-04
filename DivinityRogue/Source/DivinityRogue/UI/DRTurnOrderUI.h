// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "DRTurnOrderUnitInfo.h"
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
	TSubclassOf<UDRTurnOrderUnitInfo> mUnitInfoClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> mSeparatorClass;

private:
	UFUNCTION()
	void OnCharacterAdded(ADRCharacter* newCharacter, int index);
	UFUNCTION()
	void OnCharacterRemoved(int index);
	UFUNCTION()
	void OnQueueInitialized();
	UFUNCTION()
	void OnContinuedToNextCharacter();
	void AddUnit(ADRCharacter* character);
	void AddNextUnitToEnd();
	void FadeFirstUnit();
	UFUNCTION()
	void OnFadeCompleted();
	UFUNCTION()
	void OnSlideCompleted();
	UDRTurnOrderUnitInfo* GetUnitInfoAt(int index);

	UPROPERTY()
	UDRTurnQueue* mTurnQueue;
	const int NumberOfTurnsToShow =10;
	int mLastIndex;
	int mCounter;
};
