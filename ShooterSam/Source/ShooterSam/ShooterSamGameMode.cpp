// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterSamCharacter.h"
#include "ShooterAI.h"

AShooterSamGameMode::AShooterSamGameMode()
{
	// stub
}

void AShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();

	AShooterSamCharacter* Player = Cast<AShooterSamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	TArray<AActor*> ShooterAiActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), ShooterAiActors);

	int32 LoopIndex = 0;

	/*for (int32 i = 0; i < ShooterAiActors.Num(); i++)
	{
		AActor* ShooterAiActor = ShooterAiActors[i];
		AShooterAI* ShooterAi = Cast<AShooterAI>(ShooterAiActor);

		if (ShooterAi)
		{
			ShooterAi->StartBehaviorTree(Player);
			UE_LOG(LogTemp, Display, TEXT("%s starting behaveour tree"), *ShooterAi->GetActorNameOrLabel());
		}
	}*/
	
	for (AActor* ShooterAiActor : ShooterAiActors)
	{
		AShooterAI* ShooterAi = Cast<AShooterAI>(ShooterAiActor);

		if (ShooterAi)
		{
			ShooterAi->StartBehaviorTree(Player);
			UE_LOG(LogTemp, Display, TEXT("%s starting behaveour tree"), *ShooterAi->GetActorNameOrLabel());
		}
	}
}
