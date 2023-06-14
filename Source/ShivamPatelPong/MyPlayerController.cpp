// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Board.h"
#include <Kismet/GameplayStatics.h>


// Called when the game starts or when spawned
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AActor* Board = UGameplayStatics::GetActorOfClass(GetWorld(), ABoard::StaticClass());
	if (Board) {
		SetViewTargetWithBlend(Board, 3.f, EViewTargetBlendFunction::VTBlend_Cubic);
	}
}