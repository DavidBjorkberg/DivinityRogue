// Fill out your copyright notice in the Description page of Project Settings.


#include "DRPlayerController.h"

#include "DRGameMode.h"
#include "DRGameplayStatics.h"
#include "DRHUD.h"
#include "NavigationSystem.h"
#include "DRCharacter.h"
#include "GameFramework/InputSettings.h"

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

	UpdateCharacterUnderCursor();
}


void ADRPlayerController::BeginPlay()
{
	Super::BeginPlay();
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mHUD = Cast<ADRHUD>(GetHUD());
	mMovementSpline = GetWorld()->SpawnActor<ADRMovementSpline>(mMovementSplineBP);
	mGameMode->mOnGameplayStateChanged.AddDynamic(this, &ADRPlayerController::OnGameplayStateChanged);
	mGameMode->mOnNewTurn.AddDynamic(this, &ADRPlayerController::OnNewTurn);
	mOnCharacterUnderCursorChanged.AddDynamic(this, &ADRPlayerController::OnCharacterUnderCursorChanged);
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
	if (!mGameMode->IsPlayersTurn()) return;
	if (mGameMode->IsInGameplayState(EGameplayState::PlanningPath))
	{
		if (mCharacterUnderCursor != nullptr)
		{
			ADRCharacter* characterInPlay = mGameMode->GetCharacterInPlay();

			if (mMouseHoverState == EMouseHoverState::EnemyCharacterInBasicAttackRange)
			{
				characterInPlay->BasicAttack(mCharacterUnderCursor);
			}
			else
			{
				characterInPlay->OrderAttackMoveToActor(mCharacterUnderCursor);
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

void ADRPlayerController::OnCharacterUnderCursorChanged(ADRCharacter* previousCharacter,
                                                        ADRCharacter* characterUnderCursor)
{
	UpdateMouseHoverState(characterUnderCursor);
	UpdateCursor();
	if (previousCharacter != nullptr)
	{
		previousCharacter->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(false);
	}
	if (characterUnderCursor != nullptr)
	{
		mHUD->ShowHoverPanel(mCharacterUnderCursor);
		characterUnderCursor->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(true);
	}
	else
	{
		mHUD->HideHoverPanel();
	}
}

void ADRPlayerController::UpdateCursor()
{
	if(mMouseHoverState == EMouseHoverState::EnemyCharacter ||
		mMouseHoverState == EMouseHoverState::EnemyCharacterInBasicAttackRange)
	{
		CurrentMouseCursor = EMouseCursor::Type::Crosshairs;
	}
	else
	{
		CurrentMouseCursor = EMouseCursor::Type::Default;
	}
}

void ADRPlayerController::UpdateMouseHoverState(ADRCharacter* characterUnderCursor)
{
	if (characterUnderCursor == nullptr)
	{
		mMouseHoverState = EMouseHoverState::NoCharacter;
	}
	else if (characterUnderCursor->GetTeam() == ETeam::ENEMY)
	{
		UDRAbility_BasicAttack* BasicAttack = mGameMode->GetCharacterInPlay()->GetAbilityComponent()->GetBasicAttack();
		if (mGameMode->IsPlayersTurn() && BasicAttack->IsInRange(characterUnderCursor))
		{
			mMouseHoverState = EMouseHoverState::EnemyCharacterInBasicAttackRange;
		}
		else
		{
			mMouseHoverState = EMouseHoverState::EnemyCharacter;
		}
	}
	else if (characterUnderCursor->GetTeam() == ETeam::PLAYER)
	{
		mMouseHoverState = EMouseHoverState::AllyCharacter;
	}
}

void ADRPlayerController::UpdateCharacterUnderCursor()
{
	FHitResult hitResult = UDRGameplayStatics::GetHitResultUnderCursor(
		GetWorld(), ECollisionChannel::ECC_Pawn);
	ADRCharacter* previousCharacter = mCharacterUnderCursor;
	if (hitResult.bBlockingHit)
	{
		if (ADRCharacter* hitCharacter = Cast<ADRCharacter>(hitResult.GetActor()))
		{
			mCharacterUnderCursor = hitCharacter;
		}
	}
	else
	{
		mCharacterUnderCursor = nullptr;
	}

	if (previousCharacter != mCharacterUnderCursor)
	{
		mOnCharacterUnderCursorChanged.Broadcast(previousCharacter, mCharacterUnderCursor);
	}
}
