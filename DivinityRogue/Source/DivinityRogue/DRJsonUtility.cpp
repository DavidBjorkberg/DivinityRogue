// Fill out your copyright notice in the Description page of Project Settings.


#include "DRJsonUtility.h"

TSharedPtr<FJsonObject> UDRJsonUtility::ReadJson(FString path)
{
	check(FPlatformFileManager::Get().GetPlatformFile().FileExists(*path))
	FString jsonString;
	FFileHelper::LoadFileToString(jsonString, *path);

	TSharedPtr<FJsonObject> retJsonObject;
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(jsonString), retJsonObject))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed deserializing Json"));
		return nullptr;
	}
	return retJsonObject;
}

void UDRJsonUtility::WriteJson(FString path, TSharedPtr<FJsonObject> jsonObject)
{
	FString jsonString;

	if (!FJsonSerializer::Serialize(jsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&jsonString, 0)))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed serializing json to string"));
		return;
	}
	if (!FFileHelper::SaveStringToFile(jsonString, *path))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed writing to file"));
	}
}

void UDRJsonUtility::WriteJson(FString path, FString content)
{
	if (!FFileHelper::SaveStringToFile(content, *path))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed writing to file"));
	}
}

void UDRJsonUtility::AppendArray(FString path, FString arrayName, TSharedPtr<FJsonObject> jsonObject)
{
	TSharedRef<FJsonObject> existingJsonObject = ReadJson(*path).ToSharedRef();
	TArray<TSharedPtr<FJsonValue>> jsonArray = existingJsonObject->GetArrayField(arrayName);

	TSharedPtr<FJsonValueObject> jsonObjectToAdd = MakeShared<FJsonValueObject>(FJsonValueObject(jsonObject));
	jsonArray.Add(jsonObjectToAdd);
	existingJsonObject->SetArrayField(arrayName, jsonArray);

	FString existingJsonString;
	FJsonSerializer::Serialize(existingJsonObject, TJsonWriterFactory<>::Create(&existingJsonString));

	WriteJson(path, existingJsonString);
}

TSharedPtr<FJsonValue> UDRJsonUtility::GetJsonObjectContainingValueFromArray(FString path, FString arrayName,
                                                                              FString fieldName, FString fieldValue)
{
	TSharedRef<FJsonObject> existingJsonObject = ReadJson(*path).ToSharedRef();
	TArray<TSharedPtr<FJsonValue>> jsonArray = existingJsonObject->GetArrayField(arrayName);

	for (TSharedPtr<FJsonValue> jsonValue : jsonArray)
	{
		if (TSharedPtr<FJsonValue> foundValue = jsonValue->AsObject()->TryGetField(fieldName))
		{
			if (foundValue->AsString() == fieldValue)
			{
				return foundValue;
			}
		}
	}
	return nullptr;
}

void UDRJsonUtility::ResetArray(FString path, FString arrayName)
{
	TSharedRef<FJsonObject> existingJsonObject = ReadJson(*path).ToSharedRef();
	TArray<TSharedPtr<FJsonValue>> jsonArray = existingJsonObject->GetArrayField(arrayName);
	jsonArray.Empty();
	existingJsonObject->SetArrayField(arrayName, jsonArray);

	FString existingJsonString;
	FJsonSerializer::Serialize(existingJsonObject, TJsonWriterFactory<>::Create(&existingJsonString));

	WriteJson(path, existingJsonString);
}
