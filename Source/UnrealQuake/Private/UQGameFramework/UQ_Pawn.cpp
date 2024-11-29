// Fill out your copyright notice in the Description page of Project Settings.


#include "UQGameFramework/UQ_Pawn.h"
#include "QuakeGame/UQ_MovementComponent.h"

AUQ_Pawn::AUQ_Pawn()
{
	PrimaryActorTick.bCanEverTick = true;

	UQ_MovementComponent = CreateDefaultSubobject<UUQ_MovementComponent>(TEXT("UQ_MovementComponent"));
}

void AUQ_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUQ_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUQ_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

