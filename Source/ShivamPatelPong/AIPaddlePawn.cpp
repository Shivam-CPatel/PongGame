// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPaddlePawn.h"

// Sets default values
AAIPaddlePawn::AAIPaddlePawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DifficultyFactor = 600;
}

// Called when the game starts or when spawned
void AAIPaddlePawn::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	
}

// Called every frame
void AAIPaddlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Ball) {
		FVector BallLocation = Ball->GetActorLocation();
		FVector TargetLocation = GetActorLocation();
		TargetLocation.Y = BallLocation.Y;
		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), TargetLocation, DeltaTime, DifficultyFactor));
	}
	else
	{
		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), InitialLocation, DeltaTime, DifficultyFactor));
	}
}

void AAIPaddlePawn::SetBall(ABouncyBall* BallToSet)
{
	this->Ball = BallToSet;
}

