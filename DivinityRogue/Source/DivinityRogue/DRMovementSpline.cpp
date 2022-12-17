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

// Called when the game starts or when spawned
void ADRMovementSpline::BeginPlay()
{
	Super::BeginPlay();
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
}


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
