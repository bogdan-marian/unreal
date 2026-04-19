// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlayerAnimInstance.h"

void UPlayerAnimInstance::UpdateVelocity()
{
	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn)
	{
		return;
	}

	FVector Velocity = Pawn->GetVelocity();

	CurrentVelocity = static_cast<float>(Velocity.Length());
}
