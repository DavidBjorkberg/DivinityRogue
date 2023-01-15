// Fill out your copyright notice in the Description page of Project Settings.


#include "DRBlock.h"

#include "NavLinkCustomComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ADRBlock::ADRBlock()
{
	mTraceLength = 600;
	mPadding = 50;
}

void ADRBlock::BeginPlay()
{
	Super::BeginPlay();
	TArray<FVector> directions = {
		FVector(1, 0, 0),
		FVector(0, -1, 0),
		FVector(-1, 0, 0),
		FVector(0, 1, 0)
	};
	for (int i = 0; i < directions.Num(); i++)
	{
		if (!CheckDirection(directions[i]))
		{
			CreateNavLinkInDirection(directions[i]);
		}
	}
}

void ADRBlock::CreateNavLinkInDirection(FVector direction)
{
	ANavLinkProxy* navLink = GetWorld()->SpawnActor<ANavLinkProxy>(mNavLinkClass);

	FVector startPos = GetActorLocation() + FVector(0, 0, GetActorHalfHeight()*2) + direction * GetActorHalfWidth() - (mPadding * direction);
	navLink->SetActorLocation(startPos);
	FVector endPos = FVector(0, 0, -GetActorHalfHeight()*2) + direction * 150;
	navLink->GetSmartLinkComp()->SetLinkData(FVector(0, 0, 0), endPos, ENavLinkDirection::BothWays);
}

bool ADRBlock::CheckDirection(FVector direction)
{
	FVector startPos = GetActorLocation() - FVector(0, 0, -100);
	FVector endPos = startPos + direction * mTraceLength;

	FHitResult hit;
	return GetWorld()->LineTraceSingleByChannel(hit, startPos, endPos, ECollisionChannel::ECC_WorldStatic);
}

float ADRBlock::GetActorHalfWidth()
{
	return GetStaticMeshComponent()->Bounds.BoxExtent.X;
}

float ADRBlock::GetActorHalfHeight()
{
	return GetStaticMeshComponent()->Bounds.BoxExtent.Z;
}
