// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlayerAnimInstance.h"

void UPlayerAnimInstance::UpdateSpeed()
{
	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn)
	{
		return;
	}

	FVector Velocity = Pawn->GetVelocity();

	CurrentSpeed = static_cast<float>(Velocity.Length());
}

void UPlayerAnimInstance::HandleUpdatedTarget(AActor* NewTargetActorRef)
{
	bIsInCombat = IsValid(NewTargetActorRef);
}

void UPlayerAnimInstance::UpdateDirection()
{
	APawn* PawnRef = TryGetPawnOwner();
	if (!IsValid(PawnRef))
	{
		return;
	}

	if (!bIsInCombat)
	{
		return;
	}

	CurrentDirection = CalculateDirection(
		PawnRef->GetVelocity(),
		PawnRef->GetActorRotation());
	
}
