// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LAI_AIController.generated.h"

class UBehaviorTreeComponent;
class ATargetPoint;

/**
 * 
 */
UCLASS()
class INTROTOAI_API ALAI_AIController : public AAIController
{
	GENERATED_BODY()

public:

	// Constructor
	ALAI_AIController();

	virtual void OnPossess(APawn* InPawn) override;

	// Variables
	UPROPERTY(EditAnywhere, Category = "AIData")
	TObjectPtr<UBehaviorTree> BehaviorTreePtr;
	UPROPERTY(EditAnywhere, Category = "AIData")
	TObjectPtr<UBlackboardData> BlackboardDataPtr;
	UPROPERTY(EditAnywhere, Category = "AIData")
	TArray<ATargetPoint*> TargetPointArray;


	// Components
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComponent;
	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;

};
