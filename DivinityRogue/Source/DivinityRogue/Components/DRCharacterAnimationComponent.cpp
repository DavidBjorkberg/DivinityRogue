// Fill out your copyright notice in the Description page of Project Settings.


#include "DRCharacterAnimationComponent.h"

#include "DRCharacter.h"
#include "DRCharacterAnimInstance.h"
#include "DRUseAbilityNotify.h"


UDRCharacterAnimationComponent::UDRCharacterAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UDRCharacterAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayIdleAnimation();
}

void UDRCharacterAnimationComponent::SetAnimInstance(TSubclassOf<UDRCharacterAnimInstance> animInstanceClass)
{
	USkeletalMeshComponent* ownerMeshComp = Cast<ADRCharacter>(GetOwner())->GetMesh();
	ownerMeshComp->SetAnimInstanceClass(animInstanceClass);
	auto animInstance = ownerMeshComp->GetAnimInstance();
	mAttackAnimation = Cast<UDRCharacterAnimInstance>(animInstance)->mAttackAnimation;
}

void UDRCharacterAnimationComponent::PlayAttackAnimation(UDRAbility* ability)
{
	GetWorld()->GetAuthGameMode<ADRGameMode>()->SetGameplayState(EGameplayState::PerformingAbility);
	Cast<UDRUseAbilityNotify>(mAttackAnimation->Notifies[0].Notify)->SetParameters(ability);
	SetAnimState(EAnimState::ATTACK);
}

void UDRCharacterAnimationComponent::PlayIdleAnimation()
{
	SetAnimState(EAnimState::IDLE);
}

void UDRCharacterAnimationComponent::PlayRunAnimation()
{
	SetAnimState(EAnimState::MOVE);
}
