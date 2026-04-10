// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
	TowerCount = Towers.Num();
	UE_LOG(LogTemp, Display, TEXT("Tower Count: %d"), TowerCount);
	
	APawn* PlayerPawn =	UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
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
		Towers[LoopIndex];
		
		LoopIndex++;
	}
	UE_LOG(LogTemp, Display, TEXT("End of the loop!"));
}
