// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DRAbilityTargetComponent.generated.h"

UENUM()
enum class ETeam :uint8
{
	PLAYER,
	ENEMY,
	NEUTRAL
};

UCLASS()
class DIVINITYROGUE_API UDRAbilityTargetComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UDRAbilityTargetComponent();
	void SetHighlight(bool enabled);
	void TakeDamage(float DamageAmount, AActor* DamageCauser);
	void ModifyEnergy(int difference);
	void TeleportTo(FVector targetLocation);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ETeam GetTeam() const { return mTeam; }

	FText GetName() const { return mName; }
	void SetName(FText newName) { mName = newName; }
	void SetTeam(ETeam team) { mTeam = team; }
	void SetHighlightMesh(UPrimitiveComponent* mesh);
	//UFUNCTION(BlueprintCallable, BlueprintPure)
	//UBoxComponent* GetHitBox() const { return mHitBox; }

protected:
	UPROPERTY(EditDefaultsOnly)
	FText mName;
	UPROPERTY(EditDefaultsOnly)
	ETeam mTeam;
private:
	UPROPERTY()
	UPrimitiveComponent* mHighlightMesh;
};
