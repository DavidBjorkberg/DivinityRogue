#pragma once

#include "CoreMinimal.h"
#include "DRCharacterTemplate.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundCue.h"
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
	void ApplyTemplate(UDRCharacterTemplate* charTemplate);
	UPROPERTY(BlueprintAssignable)
	FHealthChanged mOnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FDied mOnDied;
protected:
	UPROPERTY(EditDefaultsOnly)
	int mMaxHealth;
private:
	UPROPERTY()
	USoundCue* mTakeDamageSoundCue;
	UPROPERTY()
	USoundCue* mDeathSoundCue;
	UPROPERTY()
	UDRCharacterTemplate* mCharTemplate; 
	int mCurrentHealth;
};
