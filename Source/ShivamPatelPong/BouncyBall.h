// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BouncyBall.generated.h"

UCLASS()
class SHIVAMPATELPONG_API ABouncyBall : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* BallMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UPaperSpriteComponent* BoardSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* BallMovementComponent;

protected:

	// Sets default values for this actor's properties
	ABouncyBall();

	// Called when the game starts or when spawned
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
