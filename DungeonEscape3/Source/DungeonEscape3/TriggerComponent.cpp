// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	UE_LOG(LogTemp, Display, TEXT("TriggerComponent finished contstructing"));
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Display, TEXT("TriggerComponent started playing!"));
	
	if (MoverActor != nullptr)
	{
		// we play
		Mover = MoverActor -> FindComponentByClass<UMover>();
		
		if (Mover != nullptr)
		{
			UE_LOG(LogTemp, Display, TEXT("Mover is found!"));
			Mover -> ShouldMove = true;
		} 
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to find mover compoent. Mover is not found!"));
		}
		
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("MoverActor is null!"));
	}
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// UE_LOG(LogTemp, Display, TEXT("TriggerComponent is ticking!"));
}
