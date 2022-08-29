// Fill out your copyright notice in the Description page of Project Settings.


#include "DRCharacter.h"

#include "DRCharacterAnimInstance.h"
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
}

void ADRCharacter::BeginPlay()
{
	Super::BeginPlay();
	mController = Cast<ADRAIController>(GetController());
	mStats.mAbilities.Empty();
	for (TSubclassOf<UDRAbility> ability : mBaseStats.mAbilities)
	{
		UDRAbility* spawnedAbility = NewObject<UDRAbility>(GetLevel(), ability);
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
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mAttackAnimation = Cast<UDRCharacterAnimInstance>(mSkeletalMeshComponent->GetAnimInstance())->mAttackAnimation;
	PlayIdleAnimation();
}

void ADRCharacter::OrderMoveToLocation(FVector targetLoc)
{
	mController->OrderMoveToLocation(targetLoc);
}

void ADRCharacter::OrderMoveToActor(AActor* targetActor)
{
	mController->OrderMoveToActor(targetActor);
}

bool ADRCharacter::TryUseAbility(UDRAbility* ability, ADRCharacter* target)
{
	if (ability->CanCast(this, target))
	{
		PlayAttackAnimation(ability, target);
		return true;
	}

	return false;
}

void ADRCharacter::OnTurnStart()
{
	ModifyEnergy(mStats.mActionPointsPerTurn);
}

void ADRCharacter::OnFinishedAttack()
{
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

void ADRCharacter::EndTurnIfOutOfActionPoints()
{
	if (mStats.mCurrentActionPoints <= 0)
	{
		mGameMode->EndTurn();
	}
}

void ADRCharacter::ModifyEnergy(int amount)
{
	check(mStats.mCurrentActionPoints + amount >= 0);
	mStats.mCurrentActionPoints = FMath::Clamp(mStats.mCurrentActionPoints + amount, 0, mStats.mMaxActionPoints);
	mOnEnergyChange.Broadcast(mStats.mCurrentActionPoints);
}

void ADRCharacter::PlayAttackAnimation(UDRAbility* ability, ADRCharacter* target)
{
	Cast<UDRUseAbilityNotify>(mAttackAnimation->Notifies[0].Notify)->SetParameters(ability, this, target);
	UE_LOG(LogTemp, Warning, TEXT("%s: Changed state:ATTACK"), *GetActorLabel()); 
	SetAnimState(EAnimState::ATTACK);
}

void ADRCharacter::PlayIdleAnimation()
{
	UE_LOG(LogTemp, Warning, TEXT("%s: Changed state:IDLE"), *GetActorLabel()); 
	SetAnimState(EAnimState::IDLE);
}

void ADRCharacter::PlayRunAnimation()
{
	UE_LOG(LogTemp, Warning, TEXT("%s: Changed state:MOVE"), *GetActorLabel()); 
	SetAnimState(EAnimState::MOVE);
}
