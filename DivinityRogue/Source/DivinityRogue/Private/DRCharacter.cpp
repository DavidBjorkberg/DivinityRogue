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

void ADRCharacter::MoveToLocation(FVector targetLoc)
{
	mController->MoveToLocation(targetLoc);
}

void ADRCharacter::BeginPlay()
{
	Super::BeginPlay();
	mCurrentHealth = mMaxHealth;
	mController = Cast<ADRAIController>(GetController());
	for (TSubclassOf<UDRAbility> ability : mAbilities)
	{
		UDRAbility* spawnedAbility = NewObject<UDRAbility>(GetLevel(), ability);
		mSpawnedAbilities.Add(spawnedAbility);
	}
	mHealthBar = Cast<UDRHealthBar>(mHealthBarWidget->GetUserWidgetObject());
	mHealthBar->UpdateHealthbar(mMaxHealth,mCurrentHealth);
}

bool ADRCharacter::TryUseAbility(UDRAbility* ability, ADRCharacter* target)
{
	return ability->TryUse(this, target);
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
