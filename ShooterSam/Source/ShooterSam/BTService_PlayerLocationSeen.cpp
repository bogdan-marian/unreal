// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationSeen.h"

UBTService_PlayerLocationSeen::UBTService_PlayerLocationSeen()
{
}

void UBTService_PlayerLocationSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UE_LOG(LogTemp, Display, TEXT("Player location seen service ticked %f"), DeltaSeconds);
}
