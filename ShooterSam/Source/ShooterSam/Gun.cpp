// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneRoot);
	
	MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Muzzle Flash"));
	MuzzleFlashParticleSystem->SetupAttachment(Mesh);
	
	// ImpactParticleSystem = CreateDefaultSubobject<UNiagaraSystem>(TEXT("Impact Particle System"));
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	MuzzleFlashParticleSystem->Deactivate();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
	
	MuzzleFlashParticleSystem->Activate(true);
	
	if (OwnerController)
	{
		
		FVector ViewPointLocation;
		FRotator ViewPointRotation;

		OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
		// DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotation, 90.f, 2.f, FColor::Red, true);

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		FVector EndLocation = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;
		bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPointLocation,
		                                                  EndLocation,
		                                                  ECC_GameTraceChannel1,
		                                                  Params);
		if (IsHit)
		{
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.f, 16, FColor::Red, true);
		}
	}
}
