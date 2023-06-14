// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ShviamPatelPongGameState.generated.h"

/**
 * 
 */
UCLASS()
class SHIVAMPATELPONG_API AShviamPatelPongGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	AShviamPatelPongGameState();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "config")
		int32 PlayerScore = 0;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "config")
		int32 AIScore = 0;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
