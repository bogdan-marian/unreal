// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/TraceComponent.h"

#include "Engine/DamageEvents.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/Fighter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	SkeletalComp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsAttacking) { return; }


	// fix debug start
	TArray<FHitResult> AllResults;
	for (const FTraceSockets Socket : Sockets)
	{
		
		
		FVector StartSocketLocation = SkeletalComp->GetSocketLocation(Socket.Start);
		FVector EndSocketLocation = SkeletalComp->GetSocketLocation(Socket.End);
		FQuat ShapeRotation = SkeletalComp->GetSocketQuaternion(Socket.Rotation);

		TArray<FHitResult> OutResults;
		double WeaponDistance = FVector::Distance(StartSocketLocation, EndSocketLocation);
		FVector BoxHalfExtent = FVector(BoxCollisionLength, BoxCollisionLength, WeaponDistance);
		BoxHalfExtent /= 2.0f;
		FCollisionShape Box{FCollisionShape::MakeBox(BoxHalfExtent)};
		FCollisionQueryParams IgnoreParams{
			FName(TEXT("Ignore Params")),
			false,
			GetOwner()
		};

		bool bHasFoundTargets = GetWorld()->SweepMultiByChannel(
			OutResults,
			StartSocketLocation,
			EndSocketLocation,
			ShapeRotation,
			ECC_GameTraceChannel1,
			Box,
			IgnoreParams
		);
		
		for (FHitResult& HitResult : OutResults)
		{
			AllResults.Add(HitResult);
		}

		if (bHasFoundTargets)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found %d targets"), OutResults.Num());
		}

		if (bDebugMode)
		{
			FVector CenterPoint{
				UKismetMathLibrary::VLerp(
					StartSocketLocation,
					EndSocketLocation,
					0.5f)
			};

			UKismetSystemLibrary::DrawDebugBox(
				GetWorld(),
				CenterPoint,
				Box.GetExtent(),
				bHasFoundTargets ? FColor::Green : FColor::Red,
				ShapeRotation.Rotator(),
				1.0f,
				2.0f);
		}
	}

	// fix debug end


	if (AllResults.Num() == 0) { return; }

	float CharacterDamage{0.0f};
	IFighter* FighterRef{Cast<IFighter>(GetOwner())};
	if (FighterRef)
	{
		CharacterDamage = FighterRef->GetDamage();
	}


	FDamageEvent TargetAttackEvent;
	for (const FHitResult& HitResult : AllResults)
	{
		AActor* TargetActor = HitResult.GetActor();

		if (TargetsToIgnore.Contains(TargetActor))
		{
			continue;
		}

		TargetActor->TakeDamage(
			CharacterDamage,
			TargetAttackEvent,
			GetOwner()->GetInstigatorController(),
			GetOwner());
		TargetsToIgnore.AddUnique(TargetActor);
		
		// load the blood
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), 
			HitParticleTemplate, 
			HitResult.ImpactPoint);
		
	}
}

void UTraceComponent::HandleResetAttack()
{
	TargetsToIgnore.Empty();
}
