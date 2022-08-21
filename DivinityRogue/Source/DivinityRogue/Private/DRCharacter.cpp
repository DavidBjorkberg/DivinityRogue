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
	mSkeletalMeshComponent->SetCollisionProfileName("Pawn");
	mSkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mSkeletalMeshComponent->SetupAttachment(mRoot);

	static ConstructorHelpers::FClassFinder<UUserWidget> healthBarBP(TEXT("/Game/UI/DRHealthBar_BP"));
	mHealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	mHealthBarWidget->SetWidgetClass(healthBarBP.Class);
	mHealthBarWidget->SetDrawSize(FVector2D(140, 40));
	mHealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	mHealthBarWidget->SetRelativeLocation(FVector(0, 0, 120));
	mHealthBarWidget->SetupAttachment(mSkeletalMeshComponent);
}

void ADRCharacter::OrderMoveToLocation(FVector targetLoc)
{
	mController->OrderMoveToLocation(targetLoc);
}

void ADRCharacter::BeginPlay()
{
	Super::BeginPlay();
	mController = Cast<ADRAIController>(GetController());
	for (TSubclassOf<UDRAbility> ability : mAbilities)
	{
		UDRAbility* spawnedAbility = NewObject<UDRAbility>(GetLevel(), ability);
		mSpawnedAbilities.Add(spawnedAbility);
	}
	mHealthBar = Cast<UDRHealthBar>(mHealthBarWidget->GetUserWidgetObject());
	mHealthBar->UpdateHealthbar(mMaxHealth, mCurrentHealth);
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mAttackAnimation = Cast<UDRCharacterAnimInstance>(mSkeletalMeshComponent->GetAnimInstance())->mAttackAnimation;
	mCurrentHealth = mMaxHealth;
	mCurrentActionPoints = mStartActionPoints;
	PlayIdleAnimation();
}

bool ADRCharacter::TryUseAbility(UDRAbility* ability, ADRCharacter* target)
{
	if(ability->CanCast(this,target))
	{
		PlayAttackAnimation(ability,target);
		return true;
	}

	return false;
}

void ADRCharacter::OnTurnStart()
{
	mCurrentActionPoints = FMath::Min(mCurrentActionPoints + mActionPointsPerTurn, mMaxActionPoints);
}

void ADRCharacter::OnFinishedAttack()
{
	PlayIdleAnimation();
	EndTurnIfOutOfActionPoints();
}

float ADRCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                               AActor* DamageCauser)
{
	mCurrentHealth = FMath::Max(mCurrentHealth - DamageAmount, 0);
	mHealthBar->UpdateHealthbar(mMaxHealth, mCurrentHealth);
	if (mCurrentHealth <= 0)
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
	if(mCurrentActionPoints <= 0)
	{
		mGameMode->EndTurn();
	}
}

void ADRCharacter::ConsumeActionPoints(int amount)
{
	check(amount <= mCurrentActionPoints);
	mCurrentActionPoints -= FMath::Max(amount,0);
}

void ADRCharacter::PlayAttackAnimation(UDRAbility* ability, ADRCharacter* target)
{
	Cast<UDRUseAbilityNotify>(mAttackAnimation->Notifies[0].Notify)->SetParameters(ability,this,target);
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
