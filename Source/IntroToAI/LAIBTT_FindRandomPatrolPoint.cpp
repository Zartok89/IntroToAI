// Fill out your copyright notice in the Description page of Project Settings.


#include "LAIBTT_FindRandomPatrolPoint.h"
#include "LAI_AIController.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type ULAIBTT_FindRandomPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* AIController = OwnerComp.GetAIOwner();
	ALAI_AIController* LAIController = Cast<ALAI_AIController>(AIController);
	TArray<ATargetPoint*> TargetPoints = LAIController->TargetPointArray;

	int32 RandomTargetPointIndex = FMath::RandRange(0, TargetPoints.Num() - 1);

	OwnerComp.GetBlackboardComponent()->SetValueAsObject("NextTargetPoint", TargetPoints[RandomTargetPointIndex]);

	return EBTNodeResult::Succeeded;
}
