// Fill out your copyright notice in the Description page of Project Settings.


#include "DRPlayerController.h"

#include "DRGameMode.h"
#include "DRGameplayStatics.h"
#include "GameFramework/InputSettings.h"

ADRPlayerController::ADRPlayerController()
{
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
	FHitResult hitResult = UDRGameplayStatics::GetHitResultUnderCursor(GetWorld(),ECollisionChannel::ECC_WorldStatic);
	if(hitResult.bBlockingHit)
	{
		GetWorld()->GetAuthGameMode<ADRGameMode>()->SetTargetLocation(hitResult.Location);
	}
}

