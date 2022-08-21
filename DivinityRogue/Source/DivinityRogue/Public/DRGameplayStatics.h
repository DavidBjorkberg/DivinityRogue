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

			FVector closestPoint;
			character->GetSkeletalMeshComp()->GetClosestPointOnCollision(thisActor->GetActorLocation(), closestPoint);
			float distanceToActor = FVector::Dist(thisActor->GetActorLocation(), closestPoint);
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
