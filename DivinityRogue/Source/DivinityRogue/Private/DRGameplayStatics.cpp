// Fill out your copyright notice in the Description page of Project Settings.


#include "DRGameplayStatics.h"

#include "NavigationSystem.h"

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

bool UDRGameplayStatics::GetWalkableGroundPositionUnderCursor(const UObject* worldContextObject, FVector& outLocation)
{
	FHitResult hitResult = GetHitResultUnderCursor(worldContextObject,ECollisionChannel::ECC_WorldStatic);
	FNavLocation positionOnNavMesh;
	bool isOnNavMesh = UNavigationSystemV1::GetCurrent((UWorld*)worldContextObject)->ProjectPointToNavigation(hitResult.Location,positionOnNavMesh);
	outLocation = positionOnNavMesh.Location;
	return isOnNavMesh;
}

