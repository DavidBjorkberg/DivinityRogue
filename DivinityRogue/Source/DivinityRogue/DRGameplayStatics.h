// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRCharacter.h"
#include "DRHUD.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
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
	static bool GetGroundHitResultUnderCursor(const UObject* worldContextObject, FHitResult& outHitResult,
	                                          bool onlyWalkable);

	UFUNCTION(BlueprintPure, Category="DivinityRTS", meta =(WorldContext = "WorldContextObject"))
	static ADRCharacter* GetCharacterInPlay(const UObject* worldContextObject);
	UFUNCTION(BlueprintPure, Category = "DivinityRTS", meta = (WorldContext = "WorldContextObject"))
	static ADRHUD* GetHUD(const UObject* WorldContextObject)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		return World->GetFirstPlayerController()->GetHUD<ADRHUD>();
	}

	UFUNCTION(BlueprintPure, Category = "DivinityRTS", meta = (WorldContext = "WorldContextObject"))
	static ADRGameMode* GetDRGameMode(const UObject* WorldContextObject)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		return World->GetAuthGameMode<ADRGameMode>();
	}

	UFUNCTION(BlueprintPure, Category = "DivinityRTS", meta = (WorldContext = "WorldContextObject"))
	static UDRRoundSystem* GetRoundSystem(const UObject* WorldContextObject)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		return World->GetSubsystem<UDRRoundSystem>();
	}

	template <class T>
	UFUNCTION(BlueprintCallable, Category = "DivinityRTS")
	static void SortActorListByDistance(AActor* thisActor, TArray<T*>& actorList)
	{
		actorList.Sort([thisActor](const AActor& A, const AActor& B)
		{
			return A.GetDistanceTo(thisActor) < B.GetDistanceTo(thisActor);
		});
	}
	template <class T>
	UFUNCTION(BlueprintCallable, Category = "DivinityRTS")
	static void SortActorListByDistance(FVector location, TArray<T*>& actorList)
	{
		actorList.Sort([location](const AActor& A, const AActor& B)
		{
			return FVector::Dist2D(A.GetActorLocation(),location) < FVector::Dist2D(B.GetActorLocation(),location);
		});
	}
	template <class T>
	UFUNCTION(BlueprintCallable, Category = "DivinityRTS")
	static void SortComponentListByDistance(AActor* thisActor, TArray<T*>& componentList)
	{
		componentList.Sort([thisActor](const UActorComponent& A, const UActorComponent& B)
		{
			return A.GetOwner()->GetDistanceTo(thisActor) < B.GetOwner()->GetDistanceTo(thisActor);
		});
	}

	UFUNCTION(BlueprintCallable, Category = "DivinityRTS")
	static UDRAbilityTargetComponent* GetClosestEnemyTarget(const UObject* WorldContextObject, ADRCharacter* thisActor)
	{
		TArray<ADRCharacter*> allCharacters;
		GetAllAliveCharacters(WorldContextObject, allCharacters);
		for (int i = allCharacters.Num() - 1; i >= 0; i--)
		{
			if (allCharacters[i]->GetAbilityTargetComponent()->GetTeam() == thisActor->GetAbilityTargetComponent()->GetTeam() ||
				allCharacters[i]->GetAbilityTargetComponent()->GetTeam() == ETeam::NEUTRAL)
			{
				allCharacters.RemoveAt(i);
			}
		}
		SortActorListByDistance(thisActor, allCharacters);
		return allCharacters[0]->GetAbilityTargetComponent();
	}
	UFUNCTION(BlueprintCallable, Category = "DivinityRTS")
	static UDRAbilityTargetComponent* GetClosestEnemyTargetFromLocation(const UObject* WorldContextObject, ADRCharacter* thisActor, FVector location)
	{
		TArray<ADRCharacter*> allCharacters;
		GetAllAliveCharacters(WorldContextObject, allCharacters);
		for (int i = allCharacters.Num() - 1; i >= 0; i--)
		{
			if (allCharacters[i]->GetAbilityTargetComponent()->GetTeam() == thisActor->GetAbilityTargetComponent()->GetTeam() ||
				allCharacters[i]->GetAbilityTargetComponent()->GetTeam() == ETeam::NEUTRAL)
			{
				allCharacters.RemoveAt(i);
			}
		}
		SortActorListByDistance(location, allCharacters);
		return allCharacters[0]->GetAbilityTargetComponent();
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

			float distanceToActor = GetDistanceToEdge2D(thisActor->GetActorLocation(), character);
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
	static float GetDistanceToEdge2D(FVector location, UDRAbilityTargetComponent* otherTarget)
	{
		FVector closestPoint;
		otherTarget->GetClosestPointOnCollision(location, closestPoint);
		float distanceToActor = FVector::Dist2D(location, closestPoint);
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

	template <class T>
	UFUNCTION(BlueprintCallable, Category = "DivinityRTS", meta = (WorldContext = "WorldContextObject"))
	static void FindAllComponents(const UObject* WorldContextObject, TArray<T*>& outComponents)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			if (T* comp = It->FindComponentByClass<T>())
			{
				outComponents.Add(comp);
			}
		}
	}

	static TArray<UDRAbilityTargetComponent*> GetAllAbilityTargetsInRadius(
		const UObject* WorldContextObject, FVector location, float radius)
	{
		TArray<UDRAbilityTargetComponent*> allAbilityTargets;
		FindAllComponents<UDRAbilityTargetComponent>(WorldContextObject, allAbilityTargets);

		TArray<UDRAbilityTargetComponent*> abilityTargetsInRadius;
		for (auto abilityTarget : allAbilityTargets)
		{
			if (GetDistanceToEdge2D(location, abilityTarget) <= radius)
			{
				abilityTargetsInRadius.Add(abilityTarget);
			}
		}
		return abilityTargetsInRadius;
	}

	UFUNCTION(BlueprintPure, Category = "DivinityRTS", meta = (WorldContext = "WorldContextObject"))
	static void GetAllAlivePlayerCharacters(const UObject* WorldContextObject, TArray<ADRCharacter*>& playerList);
	UFUNCTION(BlueprintPure, Category = "DivinityRTS", meta = (WorldContext = "WorldContextObject"))
	static void GetAllAliveEnemyCharacters(const UObject* WorldContextObject, TArray<ADRCharacter*>& enemyList);
	UFUNCTION(BlueprintPure, Category = "DivinityRTS", meta = (WorldContext = "WorldContextObject"))
	static void GetAllAliveCharacters(const UObject* WorldContextObject, TArray<ADRCharacter*>& characterList);
	UFUNCTION(BlueprintPure, Category = "DivinityRTS", meta = (WorldContext = "WorldContextObject"))
	static void GetAllPlayerCharacters(const UObject* WorldContextObject, TArray<ADRCharacter*>& playerList);
	UFUNCTION(BlueprintPure, Category = "DivinityRTS", meta = (WorldContext = "WorldContextObject"))
	static void GetAllEnemyCharacters(const UObject* WorldContextObject, TArray<ADRCharacter*>& enemyList);
};
