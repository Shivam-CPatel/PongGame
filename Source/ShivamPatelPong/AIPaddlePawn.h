// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Board.h"
#include "BouncyBall.h"
#include "PaddlePawn.h"
#include "AIPaddlePawn.generated.h"

UCLASS()
class SHIVAMPATELPONG_API AAIPaddlePawn : public APaddlePawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIPaddlePawn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		class ABouncyBall* Ball;

	UPROPERTY()
		FVector InitialLocation;

	UPROPERTY(EditAnywhere, Category = "Difficulty Factor")
		float DifficultyFactor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "AAA")
		void SetBall(ABouncyBall* BallToSet);
};
