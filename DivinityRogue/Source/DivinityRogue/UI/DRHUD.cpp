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

void ADRHUD::BeginPlay()
{
	Super::BeginPlay();
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mRoundSystem = GetWorld()->GetSubsystem<UDRRoundSystem>();
	Cast<ADRPlayerController>(GetWorld()->GetFirstPlayerController())->mOnMouseHoverStateChanged.AddDynamic(
		this, &ADRHUD::OnMouseHoverStateChanged);
	mScreenUI = CreateWidget<UDRScreenUI>(GetGameInstance(), mScreenUIClass);
	mScreenUI->AddToViewport(9999);
}

void ADRHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawFloatingDamageTexts();
	if (!mRoundSystem->IsPlayersTurn()) return;

	if (mGameMode->IsInGameplayState(EGameplayState::SelectingTarget))
	{
		DrawAbilityRangeCircle();
	}
	else if (mGameMode->IsInGameplayState(EGameplayState::PlanningPath))
	{
		DrawAbilityCostText();
	}
}

void ADRHUD::ShowHoverPanel(UDRAbilityTargetComponent* selectableComp)
{
	mScreenUI->ShowHoverPanel(selectableComp);
}

void ADRHUD::HideHoverPanel()
{
	mScreenUI->HideHoverCharacterPanel();
}

void ADRHUD::ShowGameOverScreen()
{
	mScreenUI->SetVisibility(ESlateVisibility::Collapsed);
	UDRGameOverUI* gameOverUI = CreateWidget<UDRGameOverUI>(GetWorld(), mGameOverUIClass);
	gameOverUI->SetValues(0);
	gameOverUI->AddToViewport();
}

void ADRHUD::ShowNextMapSelect()
{
	UUserWidget* nextMapSelect = CreateWidget<UUserWidget>(GetWorld(),mNextMapSelectClass);
	nextMapSelect->AddToViewport();
}

void ADRHUD::SpawnFloatingDamageText(AActor* damagedActor, int damage, bool isHeal)
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	FVector2d screenLocation;
	pc->ProjectWorldLocationToScreen(damagedActor->GetActorLocation(), screenLocation);
	ADRFloatingDamageText* damageText = GetWorld()->SpawnActor<ADRFloatingDamageText>(mFloatingDamageTextClass);
	damageText->SetActorLocation(damagedActor->GetActorLocation());
	FColor color = isHeal ? FColor::Green : FColor::Red;
	damageText->Initialize(damage, color);
	mFloatingDamageTexts.Add(damageText);
	//damageText->Start(damage,screenLocation);
	//damageText->AddToViewport();
}

void ADRHUD::DrawAbilityRangeCircle()
{
	const ADRCharacter* characterUsingAbility = mRoundSystem->GetCharacterInPlay();
	DrawCircle(GetWorld(), characterUsingAbility->GetActorLocation() + FVector::UpVector * 0.1f,
	           FVector::RightVector,
	           FVector::ForwardVector,
	           FColor::Orange, mGameMode->GetSelectedAbility()->GetRange(), 3000, false, -1, 0, 10);
}

void ADRHUD::DrawAbilityCostText()
{
	int energyCost = mRoundSystem->GetCharacterInPlay()->GetDRMovementComponent()->GetEnergyCostToMouse();
	float x;
	float y;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(x, y);
	DrawText(TEXT("Cost: " + FString::FromInt(energyCost + mAttackCost)), FLinearColor::Black, x + 30, y, nullptr,
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
		UDRAbility_BasicAttack* basicAttack = mRoundSystem->GetCharacterInPlay()->GetAbilityComponent()->GetBasicAttack();
		mAttackCost = basicAttack->GetAbilityInfo().mActionPointCost;
	}
	else
	{
		mAttackCost = 0;
	}
}
