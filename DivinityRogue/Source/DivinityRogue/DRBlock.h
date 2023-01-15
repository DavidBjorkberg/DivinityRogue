// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Navigation/NavLinkProxy.h"
#include "DRBlock.generated.h"

UCLASS()
class DIVINITYROGUE_API ADRBlock : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ADRBlock();
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ANavLinkProxy> mNavLinkClass;
private:
	void CreateNavLinkInDirection(FVector direction);
	bool CheckDirection(FVector direction);
	float GetActorHalfWidth();
	float GetActorHalfHeight();

	float mPadding;
	float mTraceLength;
};
