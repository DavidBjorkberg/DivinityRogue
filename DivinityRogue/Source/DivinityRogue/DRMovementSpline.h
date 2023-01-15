// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavigationPath.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "GameFramework/Actor.h"
#include "DRMovementSpline.generated.h"

class ADRGameMode;
UCLASS()
class DIVINITYROGUE_API ADRMovementSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	ADRMovementSpline();
	void DrawMovementSpline();
	void ClearSpline();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* mSplineMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USplineComponent* mSplineComp;
private:
	void CreateSplineMeshComponents(TArray<FVector> pathPoints);
	UPROPERTY()
	TArray<USplineMeshComponent*> mSplineMeshComps;
	UPROPERTY()
	ADRGameMode* mGameMode;
};
