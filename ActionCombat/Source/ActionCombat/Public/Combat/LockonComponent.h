// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "LockonComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API ULockonComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* OwnerRef;
	
	APlayerController* Controller;
	
	UCharacterMovementComponent* MovementComponent;

	class USpringArmComponent* SpringArmComp;

public:	
	// Sets default values for this component's properties
	ULockonComponent();
	
	AActor* CurrentTargetActor;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void StartLockon(float Radius = 750.0f);
	void EndLockon();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
