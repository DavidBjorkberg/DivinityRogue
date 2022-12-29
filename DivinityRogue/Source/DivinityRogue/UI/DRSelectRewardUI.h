// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRAbility.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "DRSelectRewardUI.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRSelectRewardUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void GetRandomAbilities(TSubclassOf<UDRAbility>& ability1,TSubclassOf<UDRAbility>& ability2,TSubclassOf<UDRAbility>& ability3);
protected:
	UPROPERTY(EditDefaultsOnly)
	UDataTable* abilityDataTable;
};
