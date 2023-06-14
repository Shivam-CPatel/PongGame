// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddlePawn.h"
#include "Components/BoxComponent.h"

// Sets default values
APaddlePawn::APaddlePawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PaddleCollision = CreateDefaultSubobject<UBoxComponent>("Player Root");
	
	PaddleCollision->SetSimulatePhysics(true);
	
	PaddleCollision->SetEnableGravity(false);
	
	PaddleCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	PaddleCollision->SetCollisionProfileName("BlockAllDynamic");
	
	PaddleCollision->SetBoxExtent(FVector(70, 32, 127));
	
	PaddleCollision->SetLinearDamping(10);

	PaddleCollision->GetBodyInstance()->bLockRotation = true;
	PaddleCollision->GetBodyInstance()->bLockXRotation = true;
	PaddleCollision->GetBodyInstance()->bLockYRotation = true;
	PaddleCollision->GetBodyInstance()->bLockZRotation = true;

	SetRootComponent(PaddleCollision);

	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>("Pawn Sprite");

	PaddleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PaddleMesh->SetupAttachment(RootComponent);

	Tags.Add("Paddle");
}

// Called when the game starts or when spawned
void APaddlePawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (PaddleMesh) {
		MeshHeight = PaddleCollision->Bounds.BoxExtent.Z;
	}
}

// Called every frame
void APaddlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	if (MoveUpValue != 0) {
		NewLocation = NewLocation + (GetActorRightVector() * MoveUpValue * 5);
		SetActorLocation(NewLocation);
	}
}

void APaddlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &APaddlePawn::MoveUp);
}

void APaddlePawn::MoveUp(float Value)
{
	MoveUpValue = Value;
}

