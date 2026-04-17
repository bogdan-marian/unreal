// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"

#define LOG_WARNING(x) UE_LOG(LogTemp, Warning, TEXT(x))

class Shape
{
protected:
	int32 Sides;
};

class Rectangle: public Shape
{
public:
	void SetSides();
};

void Rectangle::SetSides()
{
	Sides = 4;
}

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
	
	LOG_WARNING("This is a warining Gun BeginPlay");
	Rectangle MyRectangle;
	MyRectangle.SetSides();
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
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				GetWorld(), ImpactParticleSystem, HitResult.ImpactPoint,
				HitResult.ImpactPoint.Rotation());

			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				UGameplayStatics::ApplyDamage(HitActor, BulletDamage, OwnerController, this,
				                              UDamageType::StaticClass());
			}
		}
	}
}
