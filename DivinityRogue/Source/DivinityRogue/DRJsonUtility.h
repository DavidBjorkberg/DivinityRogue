// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DRJsonUtility.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRJsonUtility : public UObject
{
	GENERATED_BODY()
public:
	static TSharedPtr<FJsonObject> ReadJson(FString path);
	static void WriteJson(FString path, TSharedPtr<FJsonObject> jsonObject);
	static void WriteJson(FString path, FString content);
	static void AppendArray(FString path,FString arrayName,TSharedPtr<FJsonObject> jsonObject);
	static TSharedPtr<FJsonValue> GetJsonObjectContainingValueFromArray(FString path, FString arrayName, FString fieldName, FString fieldValue);
	static void ResetArray(FString path,FString arrayName);
};
