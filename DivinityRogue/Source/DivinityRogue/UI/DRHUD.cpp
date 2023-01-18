// Fill out your copyright notice in the Description page of Project Settings.


#include "DRHUD.h"

#include "DRCharacter.h"
#include "DRGameplayStatics.h"
#include "NavigationSystem.h"
#include "DRAbility.h"
#include "DRGameMode.h"
#include "DRGameOverUI.h"
#include "DRPlayerController.h"
#include "DRFloatingDamageText.h"
#include "Kismet/KismetTextLibrary.h"

void ADRHUD::BeginPlay()
{
	Super::BeginPlay();
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mRoundSystem = GetWorld()->GetSubsystem<UDRRoundSystem>();
	mPlayerController = Cast<ADRPlayerController>(GetWorld()->GetFirstPlayerController());
	mPlayerController->mOnMouseHoverStateChanged.AddDynamic(
		this, &ADRHUD::OnMouseHoverStateChanged);
	ShowBattleUI();
}

void ADRHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawFloatingDamageTexts();
	if (!mRoundSystem->IsPlayersTurn()) return;

	if (mGameMode->IsInGameplayState(EGameplayState::PlanningPath) && mPlayerController->GetMouseHoverState() !=
		EMouseHoverState::HoverUI)
	{
		DrawActionCostText();
		DrawPathLengthText();
	}
}

void ADRHUD::ShowBattleUI()
{
	mBattleUI = CreateWidget<UDRBattleUI>(GetGameInstance(), mScreenUIClass);
	mBattleUI->AddToViewport();
}

void ADRHUD::HideBattleUI()
{
	mBattleUI->RemoveFromParent();
}

void ADRHUD::ShowHoverPanel(UDRAbilityTargetComponent* selectableComp)
{
	mBattleUI->ShowHoverPanel(selectableComp);
}

void ADRHUD::HideHoverPanel()
{
	mBattleUI->HideHoverCharacterPanel();
}

void ADRHUD::ShowGameOverScreen()
{
	mBattleUI->SetVisibility(ESlateVisibility::Collapsed);
	UDRGameOverUI* gameOverUI = CreateWidget<UDRGameOverUI>(GetWorld(), mGameOverUIClass);
	gameOverUI->SetValues(0);
	gameOverUI->AddToViewport();
}

void ADRHUD::ShowNextMapSelect()
{
	UUserWidget* nextMapSelect = CreateWidget<UUserWidget>(GetWorld(), mNextMapSelectClass);
	nextMapSelect->AddToViewport();
}

void ADRHUD::ShowSelectRewardScreen()
{
	mSelectRewardUI = CreateWidget<UUserWidget>(GetWorld(), mSelectRewardClass);
	mSelectRewardUI->AddToViewport();
}

void ADRHUD::HideSelectRewardScreen()
{
	mSelectRewardUI->RemoveFromParent();
}

void ADRHUD::SpawnFloatingDamageText(AActor* damagedActor, int damage, bool isHeal)
{
	FVector2d screenLocation;
	mPlayerController->ProjectWorldLocationToScreen(damagedActor->GetActorLocation(), screenLocation);
	ADRFloatingDamageText* damageText = GetWorld()->SpawnActor<ADRFloatingDamageText>(mFloatingDamageTextClass);
	damageText->SetActorLocation(damagedActor->GetActorLocation());
	FColor color = isHeal ? FColor::Green : FColor::Red;
	damageText->Initialize(damage, color);
	mFloatingDamageTexts.Add(damageText);
}

void ADRHUD::DrawAbilityRangeCircle()
{
	const ADRCharacter* characterUsingAbility = mRoundSystem->GetCharacterInPlay();
	DrawCircle(GetWorld(), characterUsingAbility->GetActorLocation() + FVector::UpVector * 0.1f,
	           FVector::RightVector,
	           FVector::ForwardVector,
	           FColor::Orange, mGameMode->GetSelectedAbility()->GetRange(), 3000, false, -1, 0, 10);
}

void ADRHUD::DrawActionCostText()
{
	int energyCost = mRoundSystem->GetCharacterInPlay()->GetDRMovementComponent()->GetEnergyCostToMouse();
	float x;
	float y;
	int totalCost = energyCost + mAttackCost;
	int currentEnergy = mRoundSystem->GetCharacterInPlay()->GetStatsComponent()->GetStats().mCurrentEnergy;
	bool canAfford = currentEnergy >= totalCost;
	mPlayerController->GetMousePosition(x, y);
	DrawText(TEXT("Cost: " + FString::FromInt(totalCost)),
	         canAfford ? FLinearColor::Black : FLinearColor::Red, x + 30,
	         y,
	         nullptr,
	         1.5);
}

void ADRHUD::DrawPathLengthText()
{
	float pathLength = mRoundSystem->GetCharacterInPlay()->GetDRMovementComponent()->GetPathLengthToMouse();
	float x;
	float y;
	mPlayerController->GetMousePosition(x, y);

	float pathLengthInMeters = pathLength / 100.0f;
	FString pathLengthText = FString::SanitizeFloat(pathLengthInMeters);
	int index;
	pathLengthText.FindChar('.', index);
	pathLengthText.RemoveAt(index + 2,pathLengthText.Len());
	DrawText(pathLengthText + "m",
	         FLinearColor::Black, x + 30,
	         y + 20,
	         nullptr,
	         1.5);
}

void ADRHUD::DrawFloatingDamageTexts()
{
	for (int i = mFloatingDamageTexts.Num() - 1; i >= 0; i--)
	{
		if (mFloatingDamageTexts[i]->ShouldBeDestroyed())
		{
			mFloatingDamageTexts[i]->Destroy();
			mFloatingDamageTexts.RemoveAt(i);
		}
	}
}

void ADRHUD::OnMouseHoverStateChanged(EMouseHoverState newState)
{
	if (newState == EMouseHoverState::EnemyCharacter ||
		newState == EMouseHoverState::EnemyCharacterInBasicAttackRange)
	{
		UDRAbility_BasicAttack* basicAttack = mRoundSystem->GetCharacterInPlay()->GetAbilityComponent()->
		                                                    GetBasicAttack();
		mAttackCost = basicAttack->GetAbilityInfo().mActionPointCost;
	}
	else
	{
		mAttackCost = 0;
	}
}
