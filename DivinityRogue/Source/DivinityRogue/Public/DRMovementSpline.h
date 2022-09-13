// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UFUNCTION(BlueprintImplementableEvent)
	void DrawMovementSpline();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void ClearSpline();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USplineComponent* mSplineComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<USplineMeshComponent*> mSplineMeshComps;
	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* mSplineMesh;
private:
	UPROPERTY()
	ADRGameMode* mGameMode;
};
