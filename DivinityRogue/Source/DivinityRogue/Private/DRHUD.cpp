// Fill out your copyright notice in the Description page of Project Settings.


#include "DRHUD.h"

#include "DRCharacter.h"
#include "DRGameplayStatics.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"

void ADRHUD::BeginPlay()
{
	Super::BeginPlay();
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mGameMode->mOnGameplayStateChanged.AddDynamic(this, &ADRHUD::OnGameplayStateChanged);
	mScreenUI = CreateWidget<UDRScreenUI>(GetGameInstance(), mScreenUIBP);
	mScreenUI->AddToViewport(9999);
}

void ADRHUD::DrawHUD()
{
	Super::DrawHUD();
	if (!mGameMode->IsPlayersTurn()) return;

	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		const ADRCharacter* characterUsingAbility = mGameMode->GetCharacterInPlay();
		DrawCircle(GetWorld(), characterUsingAbility->GetActorLocation() + FVector::UpVector * 0.1f,
		           FVector::RightVector,
		           FVector::ForwardVector,
		           FColor::Orange, mGameMode->mSelectedAbility->GetRange(), 3000, false, -1, 0, 10);
	}
	else if (mGameMode->IsInGameplayState(EGameplayState::PlanningPath))
	{
		const float characterMovement = mGameMode->GetCharacterInPlay()->GetCharacterStats().mMovement;
		float pathLength = mGameMode->GetPathToMouse()->GetPathLength();
		pathLength -= mGameMode->GetCharacterInPlay()->mDistanceLeftUntilEnergyCost;
		int energyCost = FMath::CeilToInt(pathLength / characterMovement);
		float x;
		float y;
		GetWorld()->GetFirstPlayerController()->GetMousePosition(x, y);
		DrawText(TEXT("Cost: " + FString::FromInt(energyCost)), FLinearColor::Black, x + 30, y, nullptr, 1.5);
	}
}


void ADRHUD::StartTargeting()
{
	mIsTargeting = true;
}

void ADRHUD::StopTargeting()
{
	mIsTargeting = false;
}

void ADRHUD::ShowHoverPanel(ADRCharacter* hoveredCharacter)
{
	mScreenUI->ShowHoverCharacterPanel(hoveredCharacter);
	mShowHoverPanel = true;
}

void ADRHUD::HideHoverPanel()
{
	mScreenUI->HideHoverCharacterPanel();
	mShowHoverPanel = false;
}

void ADRHUD::OnGameplayStateChanged(EGameplayState oldState, EGameplayState newState)
{
	if (newState == EGameplayState::SelectingTarget)
	{
		StartTargeting();
	}
	else if (oldState == EGameplayState::SelectingTarget)
	{
		StopTargeting();
	}
}
