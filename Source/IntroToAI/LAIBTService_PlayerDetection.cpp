// Fill out your copyright notice in the Description page of Project Settings.

#include "LAIBTService_PlayerDetection.h"

#include "LAI_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void ULAIBTService_PlayerDetection::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Get AI Controller and Blackboard
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return;

	UBlackboardComponent* BlackBoardComponent = AIController->GetBlackboardComponent();
	if (!BlackBoardComponent) return;

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn) return;
	
	UObject* PlayerObject = BlackBoardComponent->GetValueAsObject("PlayerActor");
	AActor* PlayerActor = Cast<AActor>(PlayerObject);
	BlackBoardComponent->SetValueAsVector("PlayerLocation", PlayerActor->GetActorLocation());
}