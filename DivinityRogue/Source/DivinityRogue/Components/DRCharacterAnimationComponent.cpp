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
	mOwner = Cast<ADRCharacter>(GetOwner());
	USkeletalMeshComponent* ownerMeshComp = mOwner->GetMesh();
	ownerMeshComp->SetAnimInstanceClass(animInstanceClass);
	auto animInstance = ownerMeshComp->GetAnimInstance();
	mAnimInstance = Cast<UDRCharacterAnimInstance>(animInstance);
}

void UDRCharacterAnimationComponent::PlayAttackAnimation(UDRAbility* ability)
{
	GetWorld()->GetAuthGameMode<ADRGameMode>()->SetGameplayState(EGameplayState::PerformingAbility);
	Cast<UDRUseAbilityNotify>(mAnimInstance->mAttackAnimation->Notifies[0].Notify)->SetParameters(ability);
	mOwner->PlayAnimMontage(mAnimInstance->mAttackAnimation);
}

void UDRCharacterAnimationComponent::PlayIdleAnimation()
{
	SetAnimState(EAnimState::IDLE);
}

void UDRCharacterAnimationComponent::PlayRunAnimation()
{
	SetAnimState(EAnimState::MOVE);
}

void UDRCharacterAnimationComponent::PlayTakeDamageAnimation()
{
	mOwner->PlayAnimMontage(mAnimInstance->mTakeDamageAnimation);
}

void UDRCharacterAnimationComponent::PlayDeathAnimation()
{
	mOwner->PlayAnimMontage(mAnimInstance->mDeathAnimation);
}
