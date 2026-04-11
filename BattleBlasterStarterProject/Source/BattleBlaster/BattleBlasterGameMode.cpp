// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
	TowerCount = Towers.Num();
	UE_LOG(LogTemp, Display, TEXT("Tower Count: %d"), TowerCount);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		Tank = Cast<ATank>(PlayerPawn);
		if (!Tank)
		{
			UE_LOG(LogTemp, Error, TEXT("Player Pawn is not a Tank"));
		}
	}

	UE_LOG(LogTemp, Display, TEXT("Start of the loop!"));
	int32 LoopIndex = 0;
	while (LoopIndex < Towers.Num())
	{
		AActor* TowerActor = Towers[LoopIndex];
		if (TowerActor)
		{
			ATower* Tower = Cast<ATower>(TowerActor);
			if (Tower)
			{
				Tower->Tank = Tank;
				UE_LOG(LogTemp, Display, TEXT("%s setting the tank variable!"), *Tower->GetActorNameOrLabel());
			}
		}

		LoopIndex++;
	}
	UE_LOG(LogTemp, Display, TEXT("End of the loop!"));
}

void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor->IsA<ATank>())
	{
		Tank->HandleDestruction();
	}
	else
	{
		if (ATower* DeadTower = Cast<ATower>(DeadActor))
		{
			UE_LOG(LogTemp, Display, TEXT("Tower died!"));

			--TowerCount;
			UE_LOG(LogTemp, Display, TEXT("Tower Count: %d"), TowerCount);
			if (TowerCount == 0)
			{
				UE_LOG(LogTemp, Display, TEXT("All towers destroyed, victory!"));
			}
		}
	}
}
