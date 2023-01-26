// Fill out your copyright notice in the Description page of Project Settings.


#include "DRUsedAbilityPopup.h"

void UDRUsedAbilityPopup::Show(ADRCharacter* character, UDRAbility* ability, float duration)
{
	FText characterName = character->GetAbilityTargetComponent()->GetCharacterName();
	mCharacterText->SetText(characterName);
	mAbilityText->SetText(ability->GetAbilityInfo().mName);
	SetVisibility(ESlateVisibility::Visible);
	FTimerHandle handle;

	GetWorld()->GetTimerManager().SetTimer(handle,
		FTimerDelegate::CreateLambda([this]
		{
			SetVisibility(ESlateVisibility::Hidden);
		}), duration, false);
}
