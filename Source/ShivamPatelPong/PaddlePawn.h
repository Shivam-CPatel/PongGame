// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaddlePawn.generated.h"

UCLASS()
class SHIVAMPATELPONG_API APaddlePawn : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaddlePawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* PaddleCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* PaddleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle Speed")
		float InterpSpeed = 10;

	UPROPERTY(BlueprintREadWrite, meta = (BlureprintProtected))
		float MeshHeight;

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetMeshHeight() const { return MeshHeight; }

private:
	float PaddleMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float MoveUpValue;

	void MoveUp(float Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponet) override;
};
