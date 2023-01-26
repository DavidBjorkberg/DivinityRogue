// Fill out your copyright notice in the Description page of Project Settings.


#include "DRBattleUI.h"
#include "DRGameMode.h"

UDRBattleUI::UDRBattleUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDRBattleUI::NativeConstruct()
{
	Super::NativeConstruct();
	ADRGameMode* gameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	gameMode->mOnGameplayStateChanged.AddDynamic(this, &UDRBattleUI::OnGameplayStateChanged);
}

void UDRBattleUI::ShowUsedAbilityPopup(ADRCharacter* character, UDRAbility* ability,float duration)
{
	mUsedAbilityPopup->Show(character,ability,duration);
}

void UDRBattleUI::OnGameplayStateChanged(EGameplayState oldState, EGameplayState newState)
{
	UDRRoundSystem* roundSystem = GetWorld()->GetSubsystem<UDRRoundSystem>();
	mEndTurnButton->SetIsEnabled(newState == EGameplayState::PlanningPath && roundSystem->IsPlayersTurn());
}
