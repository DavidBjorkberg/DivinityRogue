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
	UFUNCTION(BlueprintCallable)
	void InitializePlayerCharacters();
	void InitializePlayerCharactersWithOverrides(TArray<ADRPlayerCharacter*> playerCharacters); 
	UPROPERTY()
	TArray<UDRCharacterTemplate*> mPlayerCharacters;
	UPROPERTY(BlueprintReadWrite)
	TArray<TSubclassOf<UDRCharacterTemplate>> mPlayerCharacterClasses;
private:
	TArray<FCharacterSave> mCachedPlayerCharacters;
};
