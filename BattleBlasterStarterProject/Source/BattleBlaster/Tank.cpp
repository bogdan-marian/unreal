// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"

ATank::ATank()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(CapsuleComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	if (bool MyBool = true)
	{
		UE_LOG(LogTemp, Display, TEXT("MyBool is true"));
	}
	
	// 2. Add the Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		UE_LOG(LogTemp, Display, TEXT("PlayerController is not null"));
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			UE_LOG(LogTemp, Display, TEXT("LocalPlayer is not null"));
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				UE_LOG(LogTemp, Display, TEXT("Subsystem is not null"));
				if (DefaultMappingContext == nullptr)
				{
					UE_LOG(LogTemp, Display, TEXT("DefaultMappingContext is null"));
				}
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}

	
}


// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);
	}

    
	
}

void ATank::MoveInput()
{
	UE_LOG(LogTemp, Display, TEXT("MoveInput!"));
}
