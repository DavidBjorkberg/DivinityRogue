// Fill out your copyright notice in the Description page of Project Settings.


#include "DRHealthComponent.h"

#include "DRGameplayStatics.h"


UDRHealthComponent::UDRHealthComponent()
{
	static ConstructorHelpers::FObjectFinder<USoundCue> takeDamageSoundCue(
		TEXT("/Script/Engine.SoundCue'/Game/SFX/10_Battle_SFX/15_Impact_Flesh_02_Cue.15_Impact_Flesh_02_Cue'"));
	mTakeDamageSoundCue = takeDamageSoundCue.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> deathSoundCue(
	TEXT("/Script/Engine.SoundCue'/Game/SFX/10_Battle_SFX/69_Enemy_death_01_Cue.69_Enemy_death_01_Cue'"));
	mDeathSoundCue = deathSoundCue.Object;
}

void UDRHealthComponent::ModifyHealth(int difference)
{
	UDRGameplayStatics::GetHUD(GetWorld())->SpawnFloatingDamageText(GetOwner(), FMath::Abs(difference), difference > 0);
	mCurrentHealth = FMath::Clamp(mCurrentHealth + difference, 0, mMaxHealth);
	mCharTemplate->CurrentHealth = mCurrentHealth;
	mOnHealthChanged.Broadcast(mCurrentHealth);
	if (mCurrentHealth == 0)
	{
		UDRGameplayStatics::PlaySoundAtLocation(GetWorld(),mDeathSoundCue,GetOwner()->GetActorLocation(),FRotator(0,0,0));
		mOnDied.Broadcast();
	}
	else if(difference < 0)
	{
		UDRGameplayStatics::PlaySoundAtLocation(GetWorld(),mTakeDamageSoundCue,GetOwner()->GetActorLocation(),FRotator(0,0,0));
	}
}

void UDRHealthComponent::ApplyTemplate(UDRCharacterTemplate* charTemplate)
{
	mCharTemplate = charTemplate;
	mMaxHealth = charTemplate->MaxHealth;
	mCurrentHealth = charTemplate->CurrentHealth;
}
