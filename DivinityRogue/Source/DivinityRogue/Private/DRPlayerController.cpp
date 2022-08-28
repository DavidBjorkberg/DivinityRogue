// Fill out your copyright notice in the Description page of Project Settings.


#include "DRPlayerController.h"

#include "DRGameMode.h"
#include "DRGameplayStatics.h"
#include "DRHUD.h"
#include "NavigationSystem.h"
#include "GameFramework/InputSettings.h"
#include "NavigationPath.h"

ADRPlayerController::ADRPlayerController()
{
}

void ADRPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (mGameMode->IsInGameplayState(EGameplayState::PlanningPath) && mGameMode->IsPlayersTurn())
	{
		mMovementSpline->DrawMovementSpline();
	}
}

void ADRPlayerController::StartTargetAbility(int index)
{
	ADRCharacter* characterInPlay = mGameMode->GetCharacterInPlay();
	mGameMode->mSelectedAbility = characterInPlay->GetAbility(index);
	mGameMode->SetGameplayState(EGameplayState::SelectingTarget);
}

void ADRPlayerController::BeginPlay()
{
	Super::BeginPlay();
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mMovementSpline = GetWorld()->SpawnActor<ADRMovementSpline>(mMovementSplineBP);
	mGameMode->mOnGameplayStateChanged.AddDynamic(this,&ADRPlayerController::OnGameplayStateChanged);
	mGameMode->mOnNewTurn.AddDynamic(this,&ADRPlayerController::OnNewTurn);
}

void ADRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent == NULL)
	{
		InputComponent = NewObject<UInputComponent>(this, UInputSettings::GetDefaultInputComponentClass(),
		                                            TEXT("InputComponent"));
		InputComponent->RegisterComponent();
	}
	InputComponent->BindAction("LeftMouseButton", IE_Pressed, this,
	                           &ADRPlayerController::OnLeftMouseClick);
}

void ADRPlayerController::OnLeftMouseClick()
{
	if(!mGameMode->IsPlayersTurn()) return;

	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		FHitResult hitResult = UDRGameplayStatics::GetHitResultUnderCursor(
			GetWorld(), ECollisionChannel::ECC_Pawn);
		if (hitResult.bBlockingHit)
		{
			if (ADRCharacter* hitCharacter = Cast<ADRCharacter>(hitResult.GetActor()))
			{
				UseTargetedAbility(hitCharacter);
			}
		}
		else
		{
			mGameMode->SetGameplayState(EGameplayState::PlanningPath);
		}
	}
	else
	{
		FHitResult hitResult = UDRGameplayStatics::GetHitResultUnderCursor(
			GetWorld(), ECollisionChannel::ECC_WorldStatic);
		if (hitResult.bBlockingHit)
		{
			mGameMode->GetCharacterInPlay()->OrderMoveToLocation(hitResult.Location);
		}
	}
}

void ADRPlayerController::OnGameplayStateChanged(EGameplayState oldState, EGameplayState newState)
{
	if (oldState == EGameplayState::PlanningPath)
	{
		mMovementSpline->ClearSpline();
	}
}

void ADRPlayerController::OnNewTurn(ADRCharacter* previousCharacter, ADRCharacter* newCharacter)
{
	mMovementSpline->ClearSpline();
}

void ADRPlayerController::UseTargetedAbility(ADRCharacter* target)
{
	mGameMode->GetCharacterInPlay()->TryUseAbility(mGameMode->mSelectedAbility, target);
	mGameMode->SetGameplayState(EGameplayState::PlanningPath);
}
