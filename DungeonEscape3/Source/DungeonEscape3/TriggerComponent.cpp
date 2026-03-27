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

	if (MoverActor) // MoverActor != nullptr
	{
		// we play
		Mover = MoverActor->FindComponentByClass<UMover>();

		if (Mover) // Mover != nullptr
		{
			UE_LOG(LogTemp, Display, TEXT("Mover is found!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to find mover compoent. Mover is not found!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MoverActor is null!"));
	}

	OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// UE_LOG(LogTemp, Display, TEXT("TriggerComponent is ticking!"));
}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	if (!Mover)
	{
		Mover->ShouldMove = true;
	}
}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Mover)
	{
		Mover->ShouldMove = false;
	}
}
