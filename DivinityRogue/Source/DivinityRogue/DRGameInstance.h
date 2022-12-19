// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "DRGameInstance.generated.h"

USTRUCT()
struct FCharacterSave
{
	GENERATED_BODY()
	UPROPERTY()
	int Health;
};
UCLASS()
class DIVINITYROGUE_API UDRGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	//Converts stored actors to structs which can persists between levels.
	void CacheAllData();
	void RefreshDataFromCache();
	UPROPERTY()
	TArray<ADRCharacter*> mPlayerCharacters;
	int exp;
private:
	TArray<FCharacterSave> mCachedPlayerCharacters;
};
