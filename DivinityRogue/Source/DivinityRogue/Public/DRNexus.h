// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbilityTargetComponent.h"
#include "DRHealthComponent.h"
#include "Engine/StaticMeshActor.h"
#include "DRNexus.generated.h"

UCLASS()
class DIVINITYROGUE_API ADRNexus : public AActor
{
	GENERATED_BODY()
	
public:	
	ADRNexus();
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRAbilityTargetComponent* mAbilityTargetComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDRHealthComponent* mHealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* mStaticMeshComponent;
private:
	UFUNCTION()
	void OnDeath();
	UPROPERTY()
	USceneComponent* mRoot;
};
