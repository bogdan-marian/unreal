// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/LockonComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
ULockonComponent::ULockonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	OwnerRef = GetOwner<ACharacter>();
	Controller = GetWorld()->GetFirstPlayerController();
	MovementComponent = OwnerRef->GetCharacterMovement();
	SpringArmComp = OwnerRef->FindComponentByClass<USpringArmComponent>();
}

void ULockonComponent::StartLockon(float Radius)
{
	FHitResult OutResult;
	FVector CurrentLocation{OwnerRef->GetActorLocation()};
	// create sphere collition shape
	FCollisionShape Sphere{FCollisionShape::MakeSphere(Radius)};
	FCollisionQueryParams IgnoreParams{
		FName(TEXT("Ignore Collision Params")),
		false,
		OwnerRef
	};


	bool bHasFoundTarget{
		GetWorld()->SweepSingleByChannel(
			OutResult,
			CurrentLocation,
			CurrentLocation,
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel1,
			Sphere,
			IgnoreParams
		)
	};

	if (!bHasFoundTarget)
	{
		return;
	}

	CurrentTargetActor = Cast<AActor>(OutResult.GetActor());

	Controller->SetIgnoreLookInput(true);
	MovementComponent->bOrientRotationToMovement = false;
	MovementComponent->bUseControllerDesiredRotation = true;
	
	SpringArmComp -> TargetOffset = FVector(0.0f, 0.0f, 100.0f);
}

void ULockonComponent::EndLockon()
{
	CurrentTargetActor = nullptr;
	MovementComponent->bOrientRotationToMovement = true;
	MovementComponent->bUseControllerDesiredRotation = false;
	SpringArmComp -> TargetOffset = FVector(0.0f, 0.0f, 0.0f);
	Controller->ResetIgnoreLookInput();
}


// Called every frame
void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(CurrentTargetActor))
	{
		return;
	}

	FVector CurrentLocation{OwnerRef->GetActorLocation()};
	FVector TargetLocation{CurrentTargetActor->GetActorLocation()};
	// trick to make the target apere lower so we simplify the camera look
	TargetLocation.Z -= 125.0f;
	
	// calcualte rotation
	FRotator NewRotation{
		UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation)
	};
	Controller->SetControlRotation(NewRotation);
}
