// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "AIPaddlePawn.h"
#include "BouncyBall.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "UObject/UObjectGlobals.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineBaseTypes.h"
#include "DrawDebugHelpers.h"
#include "PaperSpriteComponent.h"
#include "Components/ArrowComponent.h"

#include "Math/UnrealMathUtility.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneRoot);

	BoardSprite = CreateAbstractDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite Component"));
	BoardSprite->SetupAttachment(RootComponent);

	UpBox = CreateDefaultSubobject<UBoxComponent>("Up Box");
	UpBox->SetBoxExtent(FVector(120, 50, 140));
	UpBox->SetCollisionProfileName("BlockAll");
	UpBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);//Enable Query and physics collisions.
	UpBox->SetRelativeLocation(FVector(0.f, 0.f, -670.f));
	UpBox->SetupAttachment(RootComponent);

	UpBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>("Up Box Mesh");
	UpBoxMesh->SetupAttachment(UpBox);

	BottomBox = CreateDefaultSubobject<UBoxComponent>("Bottom Box");
	BottomBox->SetBoxExtent(FVector(120, 50, 140));
	BottomBox->SetCollisionProfileName("BlockAll");
	BottomBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);//Enable Query and physics collisions.
	BottomBox->SetupAttachment(RootComponent);

	BottomBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>("Bottom Box Mesh");
	BottomBoxMesh->SetupAttachment(BottomBox);

	CollisionBox1 = CreateDefaultSubobject<UBoxComponent>("Collision Box 1");
	CollisionBox1->SetCollisionProfileName("OverlapAll");
	CollisionBox1->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox1->OnComponentBeginOverlap.AddDynamic(this, &ABoard::OnCollisionBoxBeginOverlap);
	CollisionBox1->SetupAttachment(RootComponent);

	CollisionBox2 = CreateDefaultSubobject<UBoxComponent>("Collision Box 2");
	CollisionBox2->SetCollisionProfileName("OverlapAll");
	CollisionBox2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox2->OnComponentBeginOverlap.AddDynamic(this, &ABoard::OnCollisionBoxBeginOverlap);
	CollisionBox2->SetupAttachment(RootComponent);

	LevelCamera = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	LevelCamera->SetupAttachment(RootComponent);

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("Spawn Point");
	SpawnPoint->SetupAttachment(RootComponent);

}

void ABoard::OnPlayer01BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABouncyBall* Ball = Cast<ABouncyBall>(OtherActor)) {
		FString Message = FString("Bouncy Ball ") + OtherActor->GetName() + FString(" Destroyed");
		PrintMessageOnScreen(Message);
		Ball->Destroy();
	}
}

void ABoard::OnPlayer02BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABouncyBall* Ball = Cast<ABouncyBall>(OtherActor)) {
		FString Message = FString("Bouncy Ball ") + OtherActor->GetName() + FString(" Destroyed");
		PrintMessageOnScreen(Message);
		Ball->Destroy();
	}
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
	//START the SpawnTimer, it will call the SpawnActor() function every "SpawnDelay" and it will loop
	FTimerManager& Timer = GetWorldTimerManager();
	Timer.SetTimer(SpawnTimer, this, &ABoard::SpawnBall, 2, true);

	SetAI_Paddle(Cast<AAIPaddlePawn>(UGameplayStatics::GetActorOfClass(GetWorld(), AAIPaddlePawn::StaticClass())));

	DrawDebugBox(GetWorld(), GetActorLocation(), CollisionBox1->GetUnscaledBoxExtent(), FColor::Orange, true, -1, 0, 10);
	DrawDebugBox(GetWorld(), GetActorLocation(), CollisionBox2->GetUnscaledBoxExtent(), FColor::Orange, true, -1, 0, 10);
}

void ABoard::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) {
		if (ABouncyBall* Ball = Cast<ABouncyBall>(OtherActor)) {
			Ball->Destroy(); ballIsSpawned = false;
		}
	}
}

void ABoard::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoard::SetCanSpawn(bool bNewCanSpawn)
{
	if (!IsValid(BallTemplate)) {
		if (!bNewCanSpawn) {
			SpawnBall();
		}
	}
}

void ABoard::SetAI_Paddle(AAIPaddlePawn* NewAI_Paddle)
{
	AI_Paddle = NewAI_Paddle;
}

void ABoard::NullifyBallRef(AActor* Ball)
{
	Ball->Reset();
}

void ABoard::SpawnBall()
{	
	if (ballIsSpawned == false) {
		FActorSpawnParameters SpawnBall;
		SpawnBall.Owner = this;
		SpawnBall.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABouncyBall* BallObj = GetWorld()->SpawnActor<ABouncyBall>(BallTemplate, SpawnPoint->GetComponentTransform(), SpawnBall);
		ballIsSpawned = true;
		if (BallObj) {
			BallObj->OnDestroyed.AddDynamic(this, &ABoard::BallDestroyed);

			AI_Paddle->SetBall(BallObj);
		}
	}
}

void ABoard::BallDestroyed(AActor* DestroyedActor)
{
	DestroyedActor->OnDestroyed.RemoveAll(this);
	ballIsSpawned = false;
}

void ABoard::PrintMessageOnScreen(FString Message)
{
	//const FString Message = FString("Ending Overlap with: ") + OtherActor->GetName();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, 10.f, FColor::Red, Message);
	}
}