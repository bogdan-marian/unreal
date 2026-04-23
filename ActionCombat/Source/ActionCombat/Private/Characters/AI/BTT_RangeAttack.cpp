// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTT_RangeAttack.h"
#include "AIController.h"
#include "GameFramework//Character.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTT_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* CharacterRef{OwnerComp.GetAIOwner()->GetPawn<ACharacter>()};

	if (!IsValid(CharacterRef)) { return EBTNodeResult::Failed; }

	CharacterRef->PlayAnimMontage(AnimMontage);

	double RandomValue = UKismetMathLibrary::RandomFloat();
	if (RandomValue > Threashold)
	{
		UE_LOG(LogTemp, Warning, TEXT("Charging at the player Random Value: %f"), RandomValue);
		Threashold = 0.9;
	}
	else
	{
		Threashold -= 0.1;
		UE_LOG(LogTemp, Warning, TEXT("Not charging threashold = %f, random %f"), Threashold, RandomValue )
	}

	return EBTNodeResult::Succeeded;
}
