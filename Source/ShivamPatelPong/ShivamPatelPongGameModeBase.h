// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShivamPatelPongGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHIVAMPATELPONG_API AShivamPatelPongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Config")
		class ABoard* Board;

	UPROPERTY(BlueprintReadOnly, Category = "Config")
		class AShviamPatelPongGameState* PongGameState;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
