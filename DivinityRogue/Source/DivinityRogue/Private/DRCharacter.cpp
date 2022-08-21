// Fill out your copyright notice in the Description page of Project Settings.


#include "DRCharacter.h"

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

	mCurrentHealth = mMaxHealth;
	mCurrentActionPoints = mStartActionPoints;
}

bool ADRCharacter::TryUseAbility(UDRAbility* ability, ADRCharacter* target)
{
	if (ability->TryUse(this, target))
	{
		return true;
	}
	return false;
}

void ADRCharacter::OnTurnStart()
{
	mCurrentActionPoints = FMath::Min(mCurrentActionPoints + mActionPointsPerTurn, mMaxActionPoints);
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

void ADRCharacter::ConsumeActionPoints(int amount)
{
	check(amount <= mCurrentActionPoints);
	mCurrentActionPoints -= amount;
	UE_LOG(LogTemp, Warning, TEXT("%i / %i"), mCurrentActionPoints, mMaxActionPoints);
	if (mCurrentActionPoints == 0)
	{
		mGameMode->EndTurn();
	}
}
