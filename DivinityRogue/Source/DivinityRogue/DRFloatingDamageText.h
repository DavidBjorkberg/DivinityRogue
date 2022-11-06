// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRFloatingDamageTextWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "DRFloatingDamageText.generated.h"

UCLASS(Blueprintable)
class DIVINITYROGUE_API ADRFloatingDamageText : public AActor
{
	GENERATED_BODY()

public:
	ADRFloatingDamageText();
	void Initialize(int damage);
	bool ShouldBeDestroyed() const { return mRemainingLifeTime <= 0; }
protected:
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UWidgetComponent* mTextWidgetComponent;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDRFloatingDamageTextWidget> mFloatingDamageTextClass;
private:
	FVector2D mCurrentLocation;
	UPROPERTY()
	USceneComponent* mRoot;
	float mTotalLifeTime = 500;
	float mRemainingLifeTime;
	float mSpeed = 80;
	FVector2D mDirection;
};
