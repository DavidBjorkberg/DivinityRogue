// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "DRHealthBar.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "DRUnitInfo.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRUnitInfo : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void Init(ADRCharacter* character);
	UFUNCTION()
	void Highlight();
	UFUNCTION()
	void Unhighlight();
	void StartSlide(float targetX);
	float mSlideDuration = 0.1f;
	UPROPERTY(Transient,meta=(BindWidgetAnim))
	UWidgetAnimation* mFadeAnim;
protected:
	UPROPERTY(meta=(BindWidget))
	USizeBox* mSizeBox;
	UPROPERTY(meta=(BindWidget))
	UImage* mImage;
	UPROPERTY(meta=(BindWidget))
	UBorder* mBorder;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* mNameText;
	UPROPERTY(meta=(BindWidget))
	UDRHealthBar* mHealthbar;
	UPROPERTY(BlueprintReadOnly)
	ADRCharacter* mCharacter;
private:
	UFUNCTION()
	void OnHealthChange(int newHealth);

	float mHighlightedSize = 1.2f;
	
	bool mIsSliding;
	float mTargetX;
	float mT;
	
};
