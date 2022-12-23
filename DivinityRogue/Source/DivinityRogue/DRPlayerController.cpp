// Fill out your copyright notice in the Description page of Project Settings.


#include "DRPlayerController.h"

#include "DRGameMode.h"
#include "DRGameplayStatics.h"
#include "DRHUD.h"
#include "NavigationSystem.h"
#include "DRCharacter.h"
#include "DRAbilityTargetComponent.h"
#include "GameFramework/InputSettings.h"

ADRPlayerController::ADRPlayerController()
{
}

void ADRPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (mGameMode->IsInGameplayState(EGameplayState::PlanningPath) && mRoundSystem->IsPlayersTurn())
	{
		mMovementSpline->DrawMovementSpline();
	}

	UpdateCharacterUnderCursor();
}


void ADRPlayerController::BeginPlay()
{
	Super::BeginPlay();
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mRoundSystem = GetWorld()->GetSubsystem<UDRRoundSystem>();
	mHUD = Cast<ADRHUD>(GetHUD());
	mMovementSpline = GetWorld()->SpawnActor<ADRMovementSpline>(mMovementSplineBP);
	mGameMode->mOnGameplayStateChanged.AddDynamic(this, &ADRPlayerController::OnGameplayStateChanged);
	mRoundSystem->mOnNewTurn.AddDynamic(this, &ADRPlayerController::OnNewTurn);
	mOnCharacterUnderCursorChanged.AddDynamic(this, &ADRPlayerController::OnSelectableUnderCursorChanged);
	SetInputMode(FInputModeGameAndUI());
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
	if (!mRoundSystem->IsPlayersTurn()) return;
	if (mGameMode->IsInGameplayState(EGameplayState::PlanningPath))
	{
		if (mSelectableUnderCursor != nullptr)
		{
			ADRCharacter* characterInPlay = mRoundSystem->GetCharacterInPlay();

			if (mMouseHoverState == EMouseHoverState::EnemyCharacterInBasicAttackRange)
			{
				characterInPlay->BasicAttack(mSelectableUnderCursor);
			}
			else
			{
				characterInPlay->OrderAttackMoveToActor(mSelectableUnderCursor);
			}
		}
		else
		{
			FHitResult hitResult = UDRGameplayStatics::GetHitResultUnderCursor(
				GetWorld(), ECollisionChannel::ECC_WorldStatic);
			if (hitResult.bBlockingHit)
			{
				mRoundSystem->GetCharacterInPlay()->OrderMoveToLocation(hitResult.Location);
			}
		}
	}
	mOnLeftMouseDown.Broadcast();
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

void ADRPlayerController::OnSelectableUnderCursorChanged(UDRAbilityTargetComponent* previousSelectableComp,
                                                         UDRAbilityTargetComponent* newSelectableComp)
{
	UpdateMouseHoverState(newSelectableComp);
	UpdateCursor();
	if (previousSelectableComp != nullptr)
	{
		previousSelectableComp->SetHighlight(false);
	}
	if (newSelectableComp != nullptr)
	{
		newSelectableComp->SetHighlight(true);
		mHUD->ShowHoverPanel(newSelectableComp);
	}
	else
	{
		mHUD->HideHoverPanel();
	}
}

void ADRPlayerController::UpdateCursor()
{
	if (mMouseHoverState == EMouseHoverState::EnemyCharacter ||
		mMouseHoverState == EMouseHoverState::EnemyCharacterInBasicAttackRange)
	{
		CurrentMouseCursor = EMouseCursor::Type::Crosshairs;
	}
	else
	{
		CurrentMouseCursor = EMouseCursor::Type::Default;
	}
}

void ADRPlayerController::UpdateMouseHoverState(UDRAbilityTargetComponent* abilityTargetUnderCursor)
{
	if (abilityTargetUnderCursor == nullptr)
	{
		mMouseHoverState = EMouseHoverState::NoCharacter;
	}
	else
	{
		ETeam targetTeam = abilityTargetUnderCursor->GetTeam();
		if (targetTeam == ETeam::ENEMY)
		{
			UDRAbility_BasicAttack* BasicAttack = mRoundSystem->GetCharacterInPlay()->GetAbilityComponent()->
			                                                 GetBasicAttack();
			if (mRoundSystem->IsPlayersTurn() && BasicAttack->IsInRange(abilityTargetUnderCursor))
			{
				mMouseHoverState = EMouseHoverState::EnemyCharacterInBasicAttackRange;
			}
			else
			{
				mMouseHoverState = EMouseHoverState::EnemyCharacter;
			}
		}
		if (targetTeam == ETeam::PLAYER)
		{
			mMouseHoverState = EMouseHoverState::AllyCharacter;
		}
	}
}

void ADRPlayerController::UpdateCharacterUnderCursor()
{
	FHitResult hitResult = UDRGameplayStatics::GetHitResultUnderCursor(
		GetWorld(), ECollisionChannel::ECC_Pawn);
	UDRAbilityTargetComponent* previousSelectable = mSelectableUnderCursor;
	if (hitResult.bBlockingHit)
	{
		if (UDRAbilityTargetComponent* hitSelectable = hitResult.GetActor()->FindComponentByClass<
			UDRAbilityTargetComponent>())
		{
			mSelectableUnderCursor = hitSelectable;
		}
	}
	else
	{
		mSelectableUnderCursor = nullptr;
	}

	if (previousSelectable != mSelectableUnderCursor)
	{
		mOnCharacterUnderCursorChanged.Broadcast(previousSelectable, mSelectableUnderCursor);
	}
}
