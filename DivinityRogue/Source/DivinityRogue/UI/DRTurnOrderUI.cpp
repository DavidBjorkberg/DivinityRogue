// Fill out your copyright notice in the Description page of Project Settings.


#include "DRTurnOrderUI.h"

#include "DRTurnOrderUnitInfo.h"
#include "Animation/WidgetAnimation.h"
#include "Components/HorizontalBoxSlot.h"

void UDRTurnOrderUI::NativeConstruct()
{
	Super::NativeConstruct();
	mTurnQueue = GetWorld()->GetSubsystem<UDRRoundSystem>()->GetTurnQueue();
	//mTurnQueue->mOnCharacterAdded.AddDynamic(this, &UDRTurnOrderUI::OnCharacterAdded);
	//mTurnQueue->mOnCharacterRemoved.AddDynamic(this, &UDRTurnOrderUI::OnCharacterRemoved);
	mTurnQueue->mOnQueueInitialized.AddDynamic(this, &UDRTurnOrderUI::OnQueueInitialized);
	mTurnQueue->mOnContinuedToNextCharacter.AddDynamic(this, &UDRTurnOrderUI::OnContinuedToNextCharacter);
	mTurnList->ClearChildren();
}

void UDRTurnOrderUI::OnCharacterAdded(ADRCharacter* newCharacter, int index)
{
	//AddUnit(newCharacter);
}

void UDRTurnOrderUI::OnCharacterRemoved(int index)
{
	mTurnList->RemoveChildAt(index);
}

void UDRTurnOrderUI::OnQueueInitialized()
{
	for (int i = 0; i < NumberOfTurnsToShow; i++)
	{
		AddNextUnitToEnd();
	}
}

void UDRTurnOrderUI::OnContinuedToNextCharacter()
{
	switch (mCounter)
	{
	case 0:
		GetUnitInfoAt(0)->Highlight();
		break;
	case 1:
		GetUnitInfoAt(0)->Unhighlight();
		GetUnitInfoAt(1)->Highlight();
		break;
	default:
		GetUnitInfoAt(1)->Unhighlight();
		AddNextUnitToEnd();
		ForceLayoutPrepass();
		for (int i = 0; i < mTurnList->GetChildrenCount(); i++)
		{
			int a = GetUnitInfoAt(i)->GetDesiredSize().X;
			GetUnitInfoAt(i)->StartSlide(-a);
		}
		float slideDuration = GetUnitInfoAt(0)->mSlideDuration;
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UDRTurnOrderUI::OnSlideCompleted, slideDuration);
		break;
	}
	mCounter++;
}

void UDRTurnOrderUI::AddUnit(ADRCharacter* character)
{
	UDRTurnOrderUnitInfo* newUnitInfo = CreateWidget<UDRTurnOrderUnitInfo>(this, mUnitInfoClass);
	newUnitInfo->Init(character);
	mTurnList->AddChild(newUnitInfo);
	Cast<UHorizontalBoxSlot>(newUnitInfo->Slot)->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	Cast<UHorizontalBoxSlot>(newUnitInfo->Slot)->SetVerticalAlignment(EVerticalAlignment::VAlign_Top);
}

void UDRTurnOrderUI::AddNextUnitToEnd()
{
	if (mLastIndex == mTurnQueue->GetQueueSize())
	{
		mLastIndex = 0;
	}
	AddUnit(mTurnQueue->GetCharacterAt(mLastIndex));
	mLastIndex++;
}

void UDRTurnOrderUI::FadeFirstUnit()
{
	GetUnitInfoAt(0)->PlayAnimation(GetUnitInfoAt(0)->mFadeAnim);
	float fadeDuration = GetUnitInfoAt(0)->mFadeAnim->GetEndTime();
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UDRTurnOrderUI::OnFadeCompleted, fadeDuration);
}

void UDRTurnOrderUI::OnFadeCompleted()
{
	GetUnitInfoAt(0)->RemoveFromParent();
	for (int i = 0; i < mTurnList->GetChildrenCount(); i++)
	{
		GetUnitInfoAt(i)->SetRenderTranslation(FVector2D(0, 0));
	}
}

void UDRTurnOrderUI::OnSlideCompleted()
{
	FadeFirstUnit();
	GetUnitInfoAt(2)->Highlight();
}

UDRTurnOrderUnitInfo* UDRTurnOrderUI::GetUnitInfoAt(int index)
{
	return Cast<UDRTurnOrderUnitInfo>(mTurnList->GetChildAt(index));
}
