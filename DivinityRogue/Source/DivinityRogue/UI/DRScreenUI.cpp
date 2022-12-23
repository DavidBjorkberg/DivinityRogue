// Fill out your copyright notice in the Description page of Project Settings.


#include "DRScreenUI.h"
#include "DRGameMode.h"

UDRScreenUI::UDRScreenUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDRScreenUI::NativeConstruct()
{
	Super::NativeConstruct();
	ADRGameMode* gameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	gameMode->mOnGameplayStateChanged.AddDynamic(this, &UDRScreenUI::OnGameplayStateChanged);
}

void UDRScreenUI::OnGameplayStateChanged(EGameplayState oldState, EGameplayState newState)
{
	UDRRoundSystem* roundSystem = GetWorld()->GetSubsystem<UDRRoundSystem>();
	mEndTurnButton->SetIsEnabled(newState == EGameplayState::PlanningPath && roundSystem->IsPlayersTurn());
}
