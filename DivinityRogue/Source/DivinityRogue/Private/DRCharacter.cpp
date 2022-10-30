// Fill out your copyright notice in the Description page of Project Settings.


#include "DRCharacter.h"

#include "DRCharacterAnimInstance.h"
#include "DRGameMode.h"
#include "Components/WidgetComponent.h"

ADRCharacter::ADRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(mRoot);
	mMovementComponent = CreateDefaultSubobject<UDRMovementComponent>("MovementComponent");
	mSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	mAnimationComponent = CreateDefaultSubobject<UDRCharacterAnimationComponent>("DRAnimationComponent");
	mStatsComponent = CreateDefaultSubobject<UDRStatsComponent>("DRStatsComponent");
	mAbilityComponent = CreateDefaultSubobject<UDRAbilityComponent>("DRAbilityComponent");
	mHealthComponent = CreateDefaultSubobject<UDRHealthComponent>("DRHealthComponent");
	mHealthComponent->mOnDied.AddDynamic(this, &ADRCharacter::Died);
	mSkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mSkeletalMeshComponent->SetupAttachment(mRoot);
	mSkeletalMeshComponent->CustomDepthStencilValue = 1; //Enables outline
	mSkeletalMeshComponent->SetReceivesDecals(false);

	mHitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	mHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mHitBox->SetCollisionProfileName("Pawn");
	mHitBox->SetCanEverAffectNavigation(false);
	mHitBox->SetupAttachment(mRoot);
	mHitBox->SetReceivesDecals(false);
}

void ADRCharacter::BeginPlay()
{
	Super::BeginPlay();
	mController = Cast<ADRAIController>(GetController());
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mOnTurnStart.AddDynamic(this, &ADRCharacter::OnTurnStart);
}


void ADRCharacter::OrderMoveToLocation(FVector targetLoc)
{
	mController->OrderMoveToLocation(targetLoc);
}

void ADRCharacter::OrderMoveToActor(ADRCharacter* targetActor)
{
	mController->OrderMoveToActor(targetActor);
}

void ADRCharacter::OrderAttackMoveToActor(ADRCharacter* targetActor)
{
	mController->OrderAttackMoveToActor(targetActor);
}

void ADRCharacter::BasicAttack(ADRCharacter* targetActor)
{
	UDRAbility_BasicAttack* basicAttack = GetAbilityComponent()->GetBasicAttack();
	basicAttack->SetTarget(targetActor);
	UseAbility(basicAttack);
}

float ADRCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                               AActor* DamageCauser)
{
	mHealthComponent->ModifyHealth(-DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ADRCharacter::Heal(int healAmount)
{
	mHealthComponent->ModifyHealth(healAmount);
}

void ADRCharacter::Died()
{
	mOnUnitDied.Broadcast(this);
	Destroy();
}


void ADRCharacter::EndTurnIfOutOfActionPoints()
{
	if (mStatsComponent->GetStats().mCurrentActionPoints <= 0)
	{
		mAnimationComponent->PlayIdleAnimation();
		mController->StopMovement();
		mGameMode->EndTurn();
	}
}

void ADRCharacter::UseAbility(UDRAbility* ability)
{
	mOnPreUsedAbility.Broadcast(ability);
	mAnimationComponent->PlayAttackAnimation(ability);
}

void ADRCharacter::OnTurnStart()
{
	ModifyEnergy(mStatsComponent->GetStats().mActionPointsPerTurn);
}

void ADRCharacter::ModifyEnergy(int amount)
{
	check(mStatsComponent->GetStats().mCurrentActionPoints + amount >= 0);
	mStatsComponent->UpdateEnergy(amount);
}
