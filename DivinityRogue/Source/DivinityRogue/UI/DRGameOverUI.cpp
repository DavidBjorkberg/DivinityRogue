// Fill out your copyright notice in the Description page of Project Settings.


#include "DRGameOverUI.h"

void UDRGameOverUI::SetValues(int nrOfRoundsSurvived)
{
	FString roundText = FString::Printf(TEXT("You survived: %i rounds!"), nrOfRoundsSurvived);
	mRoundText->SetText(FText::FromString(roundText));
}
