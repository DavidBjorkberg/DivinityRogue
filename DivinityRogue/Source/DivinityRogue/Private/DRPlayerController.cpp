// Fill out your copyright notice in the Description page of Project Settings.


#include "DRPlayerController.h"

#include "DRGameMode.h"
#include "DRGameplayStatics.h"
#include "DRHUD.h"
#include "GameFramework/InputSettings.h"

ADRPlayerController::ADRPlayerController()
{
}

void ADRPlayerController::StartTargetAbility(int index)
{
	ADRCharacter* characterInPlay = GetWorld()->GetAuthGameMode<ADRGameMode>()->GetCharacterInPlay();
	mTargetingAbility = characterInPlay->GetAbility(index);
	Cast<ADRHUD>(GetHUD())->StartTargeting(characterInPlay, mTargetingAbility);
}

void ADRPlayerController::BeginPlay()
{
	Super::BeginPlay();
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
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
	if (mTargetingAbility != nullptr)
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
			StopTargetAbility();
		}
	}
	else
	{
		FHitResult hitResult = UDRGameplayStatics::GetHitResultUnderCursor(
			GetWorld(), ECollisionChannel::ECC_WorldStatic);
		if (hitResult.bBlockingHit)
		{
			mGameMode->GetCharacterInPlay()->SetTargetLocation(hitResult.Location);
		}
	}
}

void ADRPlayerController::StopTargetAbility()
{
	mTargetingAbility = nullptr;
	Cast<ADRHUD>(GetHUD())->StopTargeting();

}

void ADRPlayerController::UseTargetedAbility(ADRCharacter* target)
{
	mGameMode->GetCharacterInPlay()->UseAbility(mTargetingAbility, target);
	StopTargetAbility();
	mGameMode->OnActionCompleted();
}
