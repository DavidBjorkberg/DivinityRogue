// Fill out your copyright notice in the Description page of Project Settings.


#include "DREnemyAIController.h"

#include "DRGameplayStatics.h"
#include "DRPlayerCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void ADREnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
}

void ADREnemyAIController::RequestAction()
{
	TArray<ADRPlayerCharacter*> allPlayerUnits = mGameMode->GetAllPlayerUnits();

	ADRPlayerCharacter* closestPlayerUnit;
	float closestDistance;
	UDRGameplayStatics::GetClosestDRCharacterInList(GetPawn(), allPlayerUnits, closestPlayerUnit, closestDistance);

	for (UDRAbility* ability : mOwner->GetAbilities())
	{
		if (ability->TryUse(mOwner, closestPlayerUnit))
		{
			mGameMode->OnActionCompleted();
			return;
		}
	}
	MoveToActor(closestPlayerUnit);
	UAIBlueprintHelperLibrary::SimpleMoveToActor(this, closestPlayerUnit);
}
