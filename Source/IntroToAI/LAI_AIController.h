// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "LAI_AIController.generated.h"

class ALAI_PlayerCharacter;
class UAIPerceptionComponent;
class ATargetPoint;
class UBehaviorTreeComponent;
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

	// Functions
	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);


	// Pointers
	UPROPERTY(EditAnywhere, Category = "Startup")
	TObjectPtr<UBlackboardData> BlackBoardDataPtr;
	UPROPERTY(EditAnywhere, Category = "Startup")
	TObjectPtr<UBehaviorTree> BehaviourTreePtr;
	UPROPERTY(EditAnywhere, Category = "Startup")
	TArray<TObjectPtr<ATargetPoint>> TargetPointObjectPtrs;
	UPROPERTY()
	TObjectPtr<ALAI_PlayerCharacter> PlayerCharacterPtr;

	// Components
	UPROPERTY()
	UBlackboardComponent* BlackBoardComponent;
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComponent;
	UPROPERTY(EditAnywhere, Category = "PawnSensing")
	UAIPerceptionComponent* AIPerceptionComponent;
	UPROPERTY(EditAnywhere, Category = "PawnSensing")
	UAISenseConfig_Sight* SightConfig;
};
