// Fill out your copyright notice in the Description page of Project Settings.


#include "DRMovementSpline.h"

#include "DRCharacter.h"
#include "DRGameplayStatics.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"

// Sets default values
ADRMovementSpline::ADRMovementSpline()
{
	mSplineComp = CreateDefaultSubobject<USplineComponent>("MovementSpline");
	mSplineComp->bDrawDebug = true;
	SetRootComponent(mSplineComp);
}

void ADRMovementSpline::DrawMovementSpline()
{
	ClearSpline();

	ADRPlayerController* pc = GetWorld()->GetFirstPlayerController<ADRPlayerController>();

	UNavigationPath* path = pc->GetPathToMouse();
	TArray<FVector> pathPoints;
	for (int i = 0; i < path->PathPoints.Num(); i++)
	{
		pathPoints.Add(path->PathPoints[i] + FVector(0, 0, 30));
	}

	mSplineComp->SetSplinePoints(pathPoints, ESplineCoordinateSpace::World);
	for (int i = 0; i < pathPoints.Num(); i++)
	{
		mSplineComp->SetSplinePointType(i, ESplinePointType::Curve);
	}

	CreateSplineMeshComponents(pathPoints);
}

void ADRMovementSpline::ClearSpline()
{
	for (int i = 0; i < mSplineMeshComps.Num(); i++)
	{
		mSplineMeshComps[i]->DestroyComponent();
	}
	mSplineMeshComps.Empty();
	if (mSplineComp)
	{
		mSplineComp->ClearSplinePoints();
	}
}

// Called when the game starts or when spawned
void ADRMovementSpline::BeginPlay()
{
	Super::BeginPlay();
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
}

void ADRMovementSpline::CreateSplineMeshComponents(TArray<FVector> pathPoints)
{
	for (int i = 0; i < pathPoints.Num() - 1; i++)
	{
		FTransform a;
		USplineMeshComponent* newSplineMeshComp = Cast<USplineMeshComponent>(
			AddComponentByClass(USplineMeshComponent::StaticClass(), false, a, true));
		newSplineMeshComp->SetMobility(EComponentMobility::Movable);
		if (pathPoints[i].Z != pathPoints[i + 1].Z)
		{
			newSplineMeshComp->SetStaticMesh(nullptr);
		}
		else
		{
			newSplineMeshComp->SetStaticMesh(mSplineMesh);
			newSplineMeshComp->SetForwardAxis(ESplineMeshAxis::Z);
		}
		FinishAddComponent(newSplineMeshComp, false, a);
		AddInstanceComponent(newSplineMeshComp);
		mSplineMeshComps.Add(newSplineMeshComp);

		FVector startPos;
		FVector startTangent;
		FVector endPos;
		FVector endTangent;
		mSplineComp->GetLocationAndTangentAtSplinePoint(i, startPos, startTangent, ESplineCoordinateSpace::Local);
		mSplineComp->GetLocationAndTangentAtSplinePoint(i + 1, endPos, endTangent, ESplineCoordinateSpace::Local);
		newSplineMeshComp->SetStartAndEnd(startPos, startTangent, endPos, endTangent);
	}
}

//
// FVector ADRMovementSpline::GetStartPos()
// {
// 	ADRCharacter* charInPlay = UDRGameplayStatics::GetCharacterInPlay(GetWorld());
// 	return charInPlay->GetActorLocation();
// }
//
// FVector ADRMovementSpline::GetEndPos()
// {
// 	ADRPlayerController* pc = GetWorld()->GetFirstPlayerController<ADRPlayerController>();
// 	UDRAbilityTargetComponent* abilityTargetUnderCursor = pc->GetAbilityTargetUnderCursor();
// 	FVector endPos;
// 	if (abilityTargetUnderCursor)
// 	{
// 		endPos = abilityTargetUnderCursor->GetOwner()->GetActorLocation();
// 	}
// 	else
// 	{
// 		endPos = UDRGameplayStatics::GetHitResultUnderCursor(GetWorld(), ECollisionChannel::ECC_WorldStatic).Location;
// 	}
// 	return endPos;
// }


// void ADRMovementSpline::DrawMovementSpline()
// {
// 	mSplineComp->ClearSplinePoints();
// 	ADRCharacter* characterInPlay = mGameMode->GetCharacterInPlay();
// 	FVector pathStart = characterInPlay->GetActorLocation();
// 	FVector pathEnd = UDRGameplayStatics::GetHitResultUnderCursor(GetWorld(), ECC_WorldStatic).Location;
// 	UNavigationPath* navPath = UNavigationSystemV1::FindPathToLocationSynchronously(
// 		GetWorld(), pathStart, pathEnd, characterInPlay);
// 	mSplineComp->SetSplinePoints(navPath->PathPoints, ESplineCoordinateSpace::World);
// 	for (int i = 0; i < mSplineComp->GetNumberOfSplinePoints() - 1; i++)
// 	{
// 		mSplineComp->SetSplinePointType(i, ESplinePointType::CurveClamped);
// 	}
// 	for (int i = 0; i < mSplineComp->GetNumberOfSplinePoints() - 2; i++)
// 	{
// 		UE_LOG(LogTemp,Warning,TEXT("Spawned mesh"));
// 		USplineMeshComponent* newSplineMeshComp = NewObject<USplineMeshComponent>(this,USplineMeshComponent::StaticClass(), FName(*FString::FromInt(i)));
// 		newSplineMeshComp->SetStaticMesh(mSplineMesh);
// 		newSplineMeshComp->SetMobility(EComponentMobility::Movable);
// 		newSplineMeshComp->RegisterComponentWithWorld(GetWorld());
// 		newSplineMeshComp->AttachToComponent(mSplineComp,FAttachmentTransformRules::KeepRelativeTransform);
// 		FVector startTangent;
// 		FVector startPos;
// 		FVector endTangent;
// 		FVector endPos;
//
// 		mSplineComp->GetLocationAndTangentAtSplinePoint(i, startTangent, startPos, ESplineCoordinateSpace::Local);
// 		mSplineComp->GetLocationAndTangentAtSplinePoint(i + 1, endTangent, endPos, ESplineCoordinateSpace::Local);
// 		startPos += FVector(0,0,5);
// 		endPos += FVector(0,0,5);
// 		newSplineMeshComp->SetStartAndEnd(startPos,startTangent,endPos,endTangent);
// 		mSplineMeshComps.Add(newSplineMeshComp);
// 	}
// }
