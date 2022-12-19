// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DRGameInstance.h"
#include "DRSaveGameManager.generated.h"

UCLASS()
class DIVINITYROGUE_API UDRSaveGameManager : public UObject
{
	GENERATED_BODY()
public:
	static void Save(const UObject* WorldContextObject);
	static void Load(const UObject* WorldContextObject);
	
	TArray<FCharacterSave> mSavedCharacters;
};
