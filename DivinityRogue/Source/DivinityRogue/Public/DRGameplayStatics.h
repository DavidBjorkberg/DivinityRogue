// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	template <class T>
	UFUNCTION(BlueprintCallable, Category = "DivinityRTS")
	static bool GetClosestActorInList(AActor* thisActor, TArray<T*> actorList, T*& outClosestActor,
	                                  float& outClosestDistance)
	{
		float closestDistance = -1;
		T* closestActor = nullptr;
		for (T* TActor : actorList)
		{
			AActor* actor = Cast<AActor>(TActor);
			
			if (actor == thisActor) continue;
			
			float distanceToActor = FVector::Dist(thisActor->GetActorLocation(), actor->GetActorLocation());
			if (closestDistance == -1 ||
				distanceToActor < closestDistance)
			{
				closestActor = TActor;
				closestDistance = distanceToActor;
			}
		}
		if (closestDistance == -1) return false;

		outClosestActor = closestActor;
		outClosestDistance = closestDistance;
		return true;
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
