// Fill out your copyright notice in the Description page of Project Settings.


#include "DREnemyCharacter.h"

#include "DREnemyAIController.h"

ADREnemyCharacter::ADREnemyCharacter()
{
}

void ADREnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	mTeam = ETeam::ENEMY;
}

void ADREnemyCharacter::OnFinishedAttack()
{
	Super::OnFinishedAttack();
	if (mCurrentActionPoints > 0)
	{
		Cast<ADREnemyAIController>(GetController())->RequestAction();
	}
}
