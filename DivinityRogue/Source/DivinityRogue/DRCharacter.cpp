// Fill out your copyright notice in the Description page of Project Settings.


#include "DRCharacter.h"

#include "DRCharacterAnimInstance.h"
#include "DRGameMode.h"
#include "DRGameplayStatics.h"
#include "DRHUD.h"
#include "Components/CapsuleComponent.h"
#include "Engine/StaticMeshActor.h"

ADRCharacter::ADRCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UDRMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	mAnimationComponent = CreateDefaultSubobject<UDRCharacterAnimationComponent>("DRAnimationComponent");
	mStatsComponent = CreateDefaultSubobject<UDRStatsComponent>("DRStatsComponent");
	mAbilityComponent = CreateDefaultSubobject<UDRAbilityComponent>("DRAbilityComponent");
	mAbilityTargetComponent = CreateDefaultSubobject<UDRAbilityTargetComponent>("DRAbilityTargetComponent");
	mAbilityTargetComponent->SetupAttachment(GetCapsuleComponent());
	mHealthComponent = CreateDefaultSubobject<UDRHealthComponent>("DRHealthComponent");
	mHealthComponent->mOnDied.AddDynamic(this, &ADRCharacter::Died);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetReceivesDecals(false);
}

void ADRCharacter::BeginPlay()
{
	Super::BeginPlay();
	mAbilityTargetComponent->SetHighlightMesh(GetMesh());
	//Cast<UCharacterMovementComponent>(GetMovementComponent())->GravityScale = 0;
	mController = Cast<ADRAIController>(GetController());
	mGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();
	mRoundSystem = GetWorld()->GetSubsystem<UDRRoundSystem>();
	mOnTurnStart.AddDynamic(this, &ADRCharacter::OnTurnStart);
}

void ADRCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void ADRCharacter::OrderMoveToLocation(FVector targetLoc)
{
	mController->OrderMoveToLocation(targetLoc);
}

void ADRCharacter::OrderMoveToActor(UDRAbilityTargetComponent* target)
{
	mController->OrderMoveToActor(target);
}

void ADRCharacter::OrderAttackMoveToActor(UDRAbilityTargetComponent* target)
{
	mController->OrderAttackMoveToActor(target);
}

bool ADRCharacter::TryBasicAttack(UDRAbilityTargetComponent* target)
{
	UDRAbility_BasicAttack* basicAttack = GetAbilityComponent()->GetBasicAttack();
	if (basicAttack->CanAffordCast() && basicAttack->IsInRange(target) && basicAttack->TrySetTarget(target))
	{
		UseAbility(basicAttack);
		return true;
	}
	return false;
}

float ADRCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                               AActor* DamageCauser)
{
	mHealthComponent->ModifyHealth(-DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ADRCharacter::Initialize(UDRCharacterTemplate* charTemplate, ETeam team)
{
	mCharacterTemplate = charTemplate;
	GetAbilityTargetComponent()->SetTeam(team);

	GetMesh()->SetSkeletalMesh(charTemplate->Mesh);
	if (charTemplate->LeftWeapon)
	{
		AStaticMeshActor* weaponMesh = GetWorld()->SpawnActor<AStaticMeshActor>();
		weaponMesh->SetMobility(EComponentMobility::Movable);
		weaponMesh->GetStaticMeshComponent()->SetStaticMesh(charTemplate->LeftWeapon);
		weaponMesh->GetStaticMeshComponent()->SetSimulatePhysics(false);
		weaponMesh->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		weaponMesh->GetStaticMeshComponent()->AttachToComponent(
			GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("LeftWeaponShield"));
		if (charTemplate->LeftWeapon->GetName().Contains("Bow"))
		{
			weaponMesh->GetStaticMeshComponent()->AddLocalRotation(FRotator(0, -90, 0));
		}
	}
	if (charTemplate->RightWeapon)
	{
		AStaticMeshActor* weaponMesh = GetWorld()->SpawnActor<AStaticMeshActor>();
		weaponMesh->SetMobility(EComponentMobility::Movable);
		weaponMesh->GetStaticMeshComponent()->SetStaticMesh(charTemplate->RightWeapon);
		weaponMesh->GetStaticMeshComponent()->SetSimulatePhysics(false);
		weaponMesh->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		weaponMesh->GetStaticMeshComponent()->AttachToComponent(
			GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("RightWeaponShield"));
		if (charTemplate->RightWeapon->GetName().Contains("Bow"))
		{
			weaponMesh->GetStaticMeshComponent()->AddLocalRotation(FRotator(0, -90, 0));
		}
	}
	mStatsComponent->ApplyTemplate(charTemplate);
	mHealthComponent->ApplyTemplate(charTemplate);
	mAbilityComponent->ApplyTemplate(charTemplate);
	mAnimationComponent->SetAnimInstance(charTemplate->AnimInstance);
	mAbilityTargetComponent->SetName(charTemplate->Name);
}

void ADRCharacter::Heal(int healAmount)
{
	mHealthComponent->ModifyHealth(healAmount);
}

void ADRCharacter::Died()
{
	GetAbilityTargetComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mOnUnitDied.Broadcast(this);
}

void ADRCharacter::EndTurnIfOutOfActionPoints()
{
	if (mStatsComponent->GetStats().mCurrentEnergy <= 0)
	{
		mAnimationComponent->PlayIdleAnimation();
		mController->StopMovement();
		mRoundSystem->EndTurn();
	}
}

void ADRCharacter::UseAbility(UDRAbility* ability)
{
	mOnPreUsedAbility.Broadcast(ability);
	if (ability->ShouldRotateUser())
	{
		FVector dirToTarget = (ability->GetTargetLocation() - GetActorLocation()).GetSafeNormal2D();
		SetActorRotation(dirToTarget.Rotation());
	}
	mAnimationComponent->PlayAttackAnimation(ability);
}

void ADRCharacter::AddAbility(TSubclassOf<UDRAbility> newAbility)
{
	mCharacterTemplate->AbilityClasses.Add(newAbility);
	mAbilityComponent->AddAbility(newAbility);
}

void ADRCharacter::OnTurnStart()
{
	mStatsComponent->ModifyEnergy(mStatsComponent->GetStats().mEnergyPerTurn);
}

UDRMovementComponent* ADRCharacter::GetDRMovementComponent()
{
	return Cast<UDRMovementComponent>(GetMovementComponent());
}
