// Fill out your copyright notice in the Description page of Project Settings.

#include "LAI_AIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

ALAI_AIController::ALAI_AIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard Component");
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviourTree Component");
}

void ALAI_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!BlackboardComponent && !BehaviorTreeComponent) return;

	UseBlackboard(BlackboardDataPtr, BlackboardComponent);
	RunBehaviorTree(BehaviorTreePtr);

	TArray<AActor*> TempActorArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), TempActorArray);
	for (AActor* Actor : TempActorArray)
	{
		ATargetPoint* TargetPointActor = Cast<ATargetPoint>(Actor);
		TargetPointArray.Add(TargetPointActor);
	}
}