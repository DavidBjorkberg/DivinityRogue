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

bool UDRGameplayStatics::GetGroundHitResultUnderCursor(const UObject* worldContextObject, FHitResult& outHitResult,
                                                       bool onlyWalkable)
{
	FHitResult hitResult = GetHitResultUnderCursor(worldContextObject, ECollisionChannel::ECC_WorldStatic);
	if (!hitResult.bBlockingHit) return false;
	outHitResult = hitResult;

	if (onlyWalkable)
	{
		FNavLocation positionOnNavMesh;
		bool isOnNavMesh = UNavigationSystemV1::GetCurrent((UWorld*)worldContextObject)->ProjectPointToNavigation(
			hitResult.Location, positionOnNavMesh);
		outHitResult.Location = positionOnNavMesh.Location;
		return isOnNavMesh;
	}
	return true;
}
