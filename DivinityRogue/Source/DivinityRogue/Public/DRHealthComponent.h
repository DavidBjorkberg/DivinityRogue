#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DRHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChanged, int, health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDied);

UCLASS()
class DIVINITYROGUE_API UDRHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDRHealthComponent();
	UFUNCTION(BlueprintPure)
	int GetMaxHealth() const { return mMaxHealth; }
	UFUNCTION(BlueprintPure)
	int GetCurrentHealth() const { return mCurrentHealth; }
	void ModifyHealth(int difference);
	UPROPERTY(BlueprintAssignable)
	FHealthChanged mOnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FDied mOnDied;
protected:
	UPROPERTY(EditDefaultsOnly)
	int mMaxHealth;
	virtual void BeginPlay() override;
private:
	int mCurrentHealth;
};
