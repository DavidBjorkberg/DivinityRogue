// Fill out your copyright notice in the Description page of Project Settings.


#include "DRGameplayStatics.h"

FHitResult UDRGameplayStatics::GetHitResultUnderCursor(const UObject* WorldContextObject, ECollisionChannel objectType)
{
	FHitResult hitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> collisionArray = {
		UEngineTypes::ConvertToObjectType(objectType),
	};
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	World->GetFirstPlayerController()->GetHitResultUnderCursorForObjects(collisionArray, true, hitResult);

	return hitResult;
}

