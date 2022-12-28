// Fill out your copyright notice in the Description page of Project Settings.


#include "DRSaveGameManager.h"

#include "DRCharacter.h"
#include "DRGameplayStatics.h"
#include "DRJsonUtility.h"
#include "JsonObjectConverter.h"

void UDRSaveGameManager::Save(const UObject* WorldContextObject)
{
	UWorld* world = WorldContextObject->GetWorld();
	TArray<ADRCharacter*> playerUnits;
	UDRGameplayStatics::GetAllAlivePlayerCharacters(world, playerUnits);

	FCharacterSave characterSave;
	characterSave.Health = playerUnits[0]->GetHealthComponent()->GetMaxHealth();

	TSharedPtr<FJsonObject> jsonObj = FJsonObjectConverter::UStructToJsonObject<FCharacterSave>(characterSave);
	UDRJsonUtility::WriteJson(FPaths::ProjectSavedDir() + TEXT("Savefile.txt"),jsonObj);
}

void UDRSaveGameManager::Load(const UObject* WorldContextObject)
{
	UWorld* world = WorldContextObject->GetWorld();
	TSharedPtr<FJsonObject> loadedJsonObj = UDRJsonUtility::ReadJson(FPaths::ProjectSavedDir() + TEXT("Savefile.txt"));
	FCharacterSave loadedCharacterSave;
	FJsonObjectConverter::JsonObjectToUStruct(loadedJsonObj.ToSharedRef(),FCharacterSave::StaticStruct(),&loadedCharacterSave);
	UE_LOG(LogTemp,Warning,TEXT("Loaded health: %i"), loadedCharacterSave.Health);
}
