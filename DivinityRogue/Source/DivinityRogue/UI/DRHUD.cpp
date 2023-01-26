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
	mPlayerController = Cast<ADRPlayerController>(GetWorld()->GetFirstPlayerController());
	ShowBattleUI();
}

void ADRHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawFloatingDamageTexts();
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

void ADRHUD::ShowUsedAbilityPopup(ADRCharacter* character, UDRAbility* ability, float duration)
{
	mBattleUI->ShowUsedAbilityPopup(character,ability,duration);
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
