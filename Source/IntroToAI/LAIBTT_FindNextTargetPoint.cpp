// Fill out your copyright notice in the Description page of Project Settings.

#include "LAIBTT_FindNextTargetPoint.h"

#include "LAI_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"

EBTNodeResult::Type ULAIBTT_FindNextTargetPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Getting Actor and accessing the correct type
	ALAI_AIController* OwningActor = Cast<ALAI_AIController>(OwnerComp.GetAIOwner());

	if (OwningActor)
	{
		int TargetPointsArraySize = OwningActor->TargetPointObjectPtrs.Num();

		int RandomTargetPoint = FMath::RandRange(0, TargetPointsArraySize - 1);

		OwningActor->BlackBoardComponent->SetValueAsObject("CurrentTargetPointActor", OwningActor->TargetPointObjectPtrs[RandomTargetPoint]);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}