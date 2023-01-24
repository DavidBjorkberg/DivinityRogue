// Fill out your copyright notice in the Description page of Project Settings.


#include "DRPlayerController.h"

#include "DRGameMode.h"
#include "DRGameplayStatics.h"
#include "DRHUD.h"
#include "NavigationSystem.h"
#include "DRCharacter.h"
#include "DRAbilityTargetComponent.h"
#include "NavigationPath.h"
#include "GameFramework/InputSettings.h"

ADRPlayerController::ADRPlayerController()
{
}

void ADRPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TickMovementSpline();
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
	mOnCharacterUnderCursorChanged.AddDynamic(this, &ADRPlayerController::OnAbilityTargetUnderCursorChanged);
	SetInputMode(FInputModeGameAndUI());
}

void ADRPlayerController::TickMovementSpline()
{
	ADRCharacter* currentChar = mRoundSystem->GetCharacterInPlay();
	if(!currentChar) return;
	
	bool isRanged = currentChar->IsRanged();
	bool hoveringEnemy = GetMouseHoverState() == Enemy || GetMouseHoverState() == EnemyInBasicAttackRange;
	bool isPlayersTurn = mRoundSystem->IsPlayersTurn();
	bool isPlanningPath = mGameMode->IsInGameplayState(EGameplayState::PlanningPath);
	bool isHoveringUI = GetMouseHoverState() == HoverUI;
	if(!isPlanningPath ||
		!isPlayersTurn ||
		isHoveringUI ||
		(hoveringEnemy && isRanged))
	{
		mMovementSpline->ClearSpline();
	}
	else
	{
		mMovementSpline->DrawMovementSpline();
	}
}

UNavigationPath* ADRPlayerController::GetPathToMouse()
{
	ADRCharacter* characterInPlay = mRoundSystem->GetCharacterInPlay();
	if (characterInPlay == nullptr)
	{
		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		return NewObject<UNavigationPath>(NavSys);
	}
	FVector pathStart = characterInPlay->GetActorLocation();
	FVector pathEnd;

	if (GetMouseHoverState() == EnemyInBasicAttackRange)
	{
		pathEnd = GetAbilityTargetUnderCursor()->GetOwner()->GetActorLocation();
	}
	else
	{
		pathEnd = UDRGameplayStatics::GetHitResultUnderCursor(GetWorld(), ECC_WorldStatic).Location;
	}
	return UNavigationSystemV1::FindPathToLocationSynchronously(
		GetWorld(), pathStart, pathEnd, characterInPlay);
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

UNavigationPath* ADRPlayerController::FindTruncatedPathToMouse()
{
	ADRCharacter* charInPlay = mRoundSystem->GetCharacterInPlay();

	float maxDistance = charInPlay->GetDRMovementComponent()->GetWalkableDistance();
	UNavigationPath* pathToMouse = GetPathToMouse();
	if (pathToMouse == nullptr)
		return nullptr;

	float walkedDistance = 0;
	TArray<float> distances;
	int lastReachedPointIndex = 0;
	for (int i = 0; i < pathToMouse->PathPoints.Num() - 1; i++)
	{
		float distance = FVector::Dist2D(pathToMouse->PathPoints[i], pathToMouse->PathPoints[i + 1]);
		distances.Add(distance);
		walkedDistance += distance;
		if (walkedDistance > maxDistance)
		{
			lastReachedPointIndex = i;
			break;
		}
	}
	if (walkedDistance <= maxDistance)
	{
		return pathToMouse;
	}
	FVector dirToNextPoint = pathToMouse->PathPoints[lastReachedPointIndex + 1] - pathToMouse->PathPoints[
		lastReachedPointIndex];
	dirToNextPoint = dirToNextPoint.GetSafeNormal();

	float remainingDistance;
	if (lastReachedPointIndex == 0)
	{
		remainingDistance = maxDistance;
	}
	else
	{
		float sumOfPreviousDistances = 0;
		for (int i = 0; i < lastReachedPointIndex; i++)
		{
			sumOfPreviousDistances += distances[i];
		}
		remainingDistance = maxDistance - sumOfPreviousDistances;
	}
	FVector newLastPoint = pathToMouse->PathPoints[lastReachedPointIndex] + dirToNextPoint * remainingDistance;
	ADRCharacter* characterInPlay = mRoundSystem->GetCharacterInPlay();
	FVector pathStart = characterInPlay->GetActorLocation();

	return UNavigationSystemV1::FindPathToLocationSynchronously(
		GetWorld(), pathStart, newLastPoint, characterInPlay);
}

void ADRPlayerController::OnLeftMouseClick()
{
	if (!mRoundSystem->IsPlayersTurn()) return;
	if (mGameMode->IsInGameplayState(EGameplayState::PlanningPath))
	{
		if (mSelectableUnderCursor != nullptr)
		{
			ADRCharacter* characterInPlay = mRoundSystem->GetCharacterInPlay();

			if (mMouseHoverState == EnemyInBasicAttackRange)
			{
				characterInPlay->TryBasicAttack(mSelectableUnderCursor);
			}
			else if(!characterInPlay->IsRanged())
			{
				characterInPlay->OrderAttackMoveToActor(mSelectableUnderCursor);
			}
		}
		else if (GetMouseHoverState() != HoverUI)
		{
			FHitResult hitResult = UDRGameplayStatics::GetHitResultUnderCursor(
				GetWorld(), ECC_WorldStatic);
			if (hitResult.bBlockingHit && GetPathToMouse()->GetPathLength() > 0)
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

void ADRPlayerController::OnAbilityTargetUnderCursorChanged(UDRAbilityTargetComponent* previousSelectableComp,
                                                            UDRAbilityTargetComponent* newSelectableComp,
                                                            EMouseHoverState newState, bool isPlayersTurn)
{
	UpdateMouseHoverState(newSelectableComp);
	mCurrentCursorWidget->UpdateCursor(newState);
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

	if (isPlayersTurn)
	{
		if (newSelectableComp != nullptr &&
			newState == Enemy ||
			newState == EnemyInBasicAttackRange)
		{
			UDRAbility* basicAttack = mRoundSystem->GetCharacterInPlay()->GetAbilityComponent()->GetBasicAttack();
			if (basicAttack->IsRanged())
			{
				float basicAttackRange = basicAttack->GetRange();
				mRoundSystem->GetCharacterInPlay()->ShowRangeIndicator(basicAttackRange);
			}
		}
		else
		{
			mRoundSystem->GetCharacterInPlay()->HideRangeIndicator();
		}
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
				mMouseHoverState = EMouseHoverState::EnemyInBasicAttackRange;
			}
			else
			{
				mMouseHoverState = EMouseHoverState::Enemy;
			}
		}
		if (targetTeam == ETeam::PLAYER)
		{
			mMouseHoverState = EMouseHoverState::Ally;
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
		if (UDRAbilityTargetComponent* hitSelectable = Cast<UDRAbilityTargetComponent>(hitResult.Component))
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
		UpdateMouseHoverState(mSelectableUnderCursor);
		mOnCharacterUnderCursorChanged.Broadcast(previousSelectable, mSelectableUnderCursor, mMouseHoverState,
		                                         mRoundSystem->IsPlayersTurn());
	}
}
