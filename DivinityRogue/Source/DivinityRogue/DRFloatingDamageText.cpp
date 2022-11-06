// Fill out your copyright notice in the Description page of Project Settings.


#include "DRFloatingDamageText.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/WidgetComponent.h"


// Sets default values
ADRFloatingDamageText::ADRFloatingDamageText()
{
	mRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(mRoot);
	mTextWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	mTextWidgetComponent->SetupAttachment(mRoot);
	PrimaryActorTick.bCanEverTick = true;
}

void ADRFloatingDamageText::Initialize(int damage)
{
	float randomX = FMath::RandRange(-0.25f, 0.25f);
	mDirection = FVector2D(randomX,-1);
	mDirection.Normalize();
	mRemainingLifeTime = mTotalLifeTime;
	mTextWidgetComponent->SetWidgetClass(mFloatingDamageTextClass);
	mCurrentLocation = FVector2d(0,0);
	Cast<UDRFloatingDamageTextWidget>(mTextWidgetComponent->GetWidget())->mDamageText->SetText(FText::FromString(FString::FromInt(damage)));
}

void ADRFloatingDamageText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	mRemainingLifeTime -= DeltaTime;
	// AddActorLocalOffset(mDirection * DeltaTime * mSpeed);
	mCurrentLocation += mDirection * DeltaTime * mSpeed;
	UWidgetLayoutLibrary::SlotAsCanvasSlot(Cast<UDRFloatingDamageTextWidget>(mTextWidgetComponent->GetWidget())->mDamageText)->SetPosition(mCurrentLocation);
}
