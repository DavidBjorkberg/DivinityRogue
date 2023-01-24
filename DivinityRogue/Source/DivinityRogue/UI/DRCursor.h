// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRRoundSystem.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DRCursor.generated.h"

class ADRPlayerController;
UENUM()
enum ECursorType
{
	Default,
	Attack,
};
enum EMouseHoverState;
UCLASS()
class DIVINITYROGUE_API UDRCursor : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void Clear();
	void TryShowOutOfRangeText();
	void TryShowCostText();
	void TryShowDistanceText();
	void UpdateCursor(EMouseHoverState newState);
	
protected:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* mDefaultTexture;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* mAttackTexture;
	UPROPERTY(meta=(BindWidget))
	UImage* mImage;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* mCostText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* mDistanceText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* mOutOfRangeText;
private:
	UPROPERTY()
	UDRRoundSystem* mRoundSystem;
	UPROPERTY()
	ADRPlayerController* mPlayerController;
	UPROPERTY()
	ADRGameMode* mGameMode;
	bool mIsInitialized;
};
