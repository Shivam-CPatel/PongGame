// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

UCLASS()
class SHIVAMPATELPONG_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();
	USceneComponent* SceneRoot;


	/*PART 2*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* UpBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* UpBoxMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* BottomBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* BottomBoxMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCameraComponent* LevelCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UPaperSpriteComponent* BoardSprite;

	UPROPERTY(EditAnywhere, Category = "Collision Box")
		class UBoxComponent* CollisionBox1;

	UPROPERTY(EditAnywhere, Category = "Collision Box")
		class UBoxComponent* CollisionBox2;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ABouncyBall> BallTemplate;

	UPROPERTY(BlueprintReadOnly, Category = "Config")
		class AShviamPatelPongGameState* PongGameState;

	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		FTimerHandle SpawnTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
		class AAIPaddlePawn* AI_Paddle;

//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
		uint32 bCanSpawn = 1;
		bool ballIsSpawned = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
		float SpawnDelay = 3.f;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* SpawnPoint;

	UFUNCTION()
		void OnPlayer01BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnPlayer02BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void  OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetCanSpawn(bool bNewCanSpawn);

	void SetAI_Paddle(AAIPaddlePawn* NewAI_Paddle);

	void PrintMessageOnScreen(FString Message);

	void NullifyBallRef(AActor* Ball);

	void SpawnBall();

	UFUNCTION()
	void BallDestroyed(AActor* DestroyedActor);
};
