// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncyBall.h"
#include "PaperSpriteComponent.h"
#include "Board.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABouncyBall::ABouncyBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereCollision);
	SphereCollision->SetSphereRadius(24.f);

	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereCollision->SetCollisionProfileName("BlockAll");

//	BoardSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BoardSprite"));
//	BoardSprite->SetupAttachment(RootComponent);
//	BoardSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SphereCollision->GetBodyInstance()->bLockZTranslation = true;

	BallMeshComponent = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("BallMesh"));
	BallMeshComponent->SetupAttachment(RootComponent);

	BallMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	BallMovementComponent->ProjectileGravityScale = 0.f;
	BallMovementComponent->InitialSpeed = 1000.f;
	BallMovementComponent->MaxSpeed = 1000.f;
	BallMovementComponent->bShouldBounce = true;
	BallMovementComponent->Bounciness = 1.1;
	BallMovementComponent->Friction = 0.f;

}

void ABouncyBall::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

