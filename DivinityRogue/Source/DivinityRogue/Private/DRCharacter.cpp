// Fill out your copyright notice in the Description page of Project Settings.


#include "DRCharacter.h"

#include "DRCharacterAnimInstance.h"
#include "DRGameMode.h"
#include "DRUseAbilityNotify.h"
#include "Components/WidgetComponent.h"

ADRCharacter::ADRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(mRoot);
	mMovementComponent = CreateDefaultSubobject<UDRMovementComponent>("MovementComponent");
	mSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	mSkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mSkeletalMeshComponent->SetupAttachment(mRoot);
	mSkeletalMeshComponent->CustomDepthStencilValue = 1; //Enables outline
	
	mHitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	mHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mHitBox->SetCollisionProfileName("Pawn");
	mHitBox->SetCanEverAffectNavigation(false);
	mHitBox->SetupAttachment(mRoot);
	mSkeletalMeshComponent->SetReceivesDecals(false);
	mHitBox->SetReceivesDecals(false);
}

void ADRCharacter::BeginPlay()
{
	Super::BeginPlay();
	mController = Cast<ADRAIController>(GetController());
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mAttackAnimation = Cast<UDRCharacterAnimInstance>(mSkeletalMeshComponent->GetAnimInstance())->mAttackAnimation;
	mOnTurnStart.AddDynamic(this, &ADRCharacter::OnTurnStart);
	ApplyBaseStats();
	PlayIdleAnimation();
}

void ADRCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ADRCharacter::OrderMoveToLocation(FVector targetLoc)
{
	mController->OrderMoveToLocation(targetLoc);
}

void ADRCharacter::OrderMoveToActor(AActor* targetActor)
{
	mController->OrderMoveToActor(targetActor);
}

float ADRCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                               AActor* DamageCauser)
{
	mStats.mCurrentHealth = FMath::Max(mStats.mCurrentHealth - DamageAmount, 0);
	mOnHealthChange.Broadcast(mStats.mCurrentHealth);
	if (mStats.mCurrentHealth <= 0)
	{
		Died();
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ADRCharacter::Died()
{
	mOnUnitDied.Broadcast(this);
	Destroy();
}

void ADRCharacter::ApplyBaseStats()
{
	mStats.mAbilities.Empty();
	for (TSubclassOf<UDRAbility> ability : mBaseStats.mAbilities)
	{
		UDRAbility* spawnedAbility = NewObject<UDRAbility>(GetLevel(), ability);
		spawnedAbility->SetOwner(this);
		mStats.mAbilities.Add(spawnedAbility);
	}
	mStats.mName = mBaseStats.mName;
	mStats.mMaxHealth = mBaseStats.mMaxHealth;
	mStats.mCurrentHealth = mBaseStats.mMaxHealth;
	mStats.mSpeed = mBaseStats.mSpeed;
	mStats.mMaxActionPoints = mBaseStats.mMaxActionPoints;
	mStats.mStartActionPoints = mBaseStats.mStartActionPoints;
	mStats.mCurrentActionPoints = mBaseStats.mStartActionPoints;
	mStats.mActionPointsPerTurn = mBaseStats.mActionPointsPerTurn;
	mStats.mMovement = mBaseStats.mMovement;
	mStats.mMovementSpeed = mBaseStats.mMovementSpeed;
}

void ADRCharacter::EndTurnIfOutOfActionPoints()
{
	if (mStats.mCurrentActionPoints <= 0)
	{
		PlayIdleAnimation();
		mController->StopMovement();
		mGameMode->EndTurn();
	}
}

void ADRCharacter::OnTurnStart()
{
	ModifyEnergy(mStats.mActionPointsPerTurn);
}

void ADRCharacter::ModifyEnergy(int amount)
{
	check(mStats.mCurrentActionPoints + amount >= 0);
	mStats.mCurrentActionPoints = FMath::Clamp(mStats.mCurrentActionPoints + amount, 0, mStats.mMaxActionPoints);
	mOnEnergyChange.Broadcast(mStats.mCurrentActionPoints);
}

void ADRCharacter::PlayAttackAnimation(UDRAbility* ability)
{
	Cast<UDRUseAbilityNotify>(mAttackAnimation->Notifies[0].Notify)->SetParameters(ability);
	SetAnimState(EAnimState::ATTACK);
}

void ADRCharacter::PlayIdleAnimation()
{
	SetAnimState(EAnimState::IDLE);
}

void ADRCharacter::PlayRunAnimation()
{
	SetAnimState(EAnimState::MOVE);
}
