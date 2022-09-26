// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "DRGameplayStatics.generated.h"

/**
 * 
 */
UCLASS()
class DIVINITYROGUE_API UDRGameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "DivinityRTS", meta = (WorldContext = "WorldContextObject"))
	static FHitResult GetHitResultUnderCursor(const UObject* WorldContextObject, ECollisionChannel objectType);
	UFUNCTION(BlueprintCallable, Category = "DivinityRTS", meta = (WorldContext = "WorldContextObject"))
	static bool GetWalkableGroundPositionUnderCursor(const UObject* worldContextObject, FVector& outLocation);
	template <class T>
	UFUNCTION(BlueprintCallable, Category = "DivinityRTS")
	static void SortActorListByDistance(AActor* thisActor, TArray<T*>& actorList)
	{
		actorList.Sort([thisActor](const AActor& A, const AActor& B)
		{
			return  A.GetDistanceTo(thisActor) > B.GetDistanceTo(thisActor);
		});
	}

	template <class T>
	UFUNCTION(BlueprintCallable, Category = "DivinityRTS")
	static bool GetClosestDRCharacterInList(AActor* thisActor, TArray<T*> actorList, T*& outClosestPawn,
	                                        float& outClosestDistance)
	{
		float closestDistance = -1;
		T* closestActor = nullptr;
		for (T* TActor : actorList)
		{
			ADRCharacter* character = Cast<ADRCharacter>(TActor);

			if (character == thisActor) continue;

			float distanceToActor = GetDistanceToEdge2D(Cast<ADRCharacter>(thisActor),character);
			if (closestDistance == -1 ||
				distanceToActor < closestDistance)
			{
				closestActor = TActor;
				closestDistance = distanceToActor;
			}
		}
		if (closestDistance == -1) return false;

		outClosestPawn = closestActor;
		outClosestDistance = closestDistance;
		return true;
	}

	UFUNCTION(BlueprintCallable, Category = "DivinityRTS", meta = (WorldContext = "WorldContextObject"))
	static float GetDistanceToEdge2D(ADRCharacter* thisActor, ADRCharacter* otherActor)
	{
		FVector closestPoint;
		float test = otherActor->GetHitBox()->GetClosestPointOnCollision(thisActor->GetActorLocation(), closestPoint);
		float distanceToActor = FVector::Dist2D(thisActor->GetActorLocation(), closestPoint);
		return distanceToActor;

	}

	template <class T>
	UFUNCTION(BlueprintCallable, Category = "DivinityRTS", meta = (WorldContext = "WorldContextObject"))
	static void FindAllActors(const UObject* WorldContextObject, TArray<T*>& outActors)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		for (TActorIterator<T> It(World); It; ++It)
		{
			outActors.Add(*It);
		}
	}
};
