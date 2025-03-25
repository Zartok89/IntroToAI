// Fill out your copyright notice in the Description page of Project Settings.

#include "LAI_AIController.h"

#include "LAI_PlayerCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

ALAI_AIController::ALAI_AIController()
{
	BlackBoardComponent = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard");
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTree");
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	// Configure Sight Sense
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = 1200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 180.0f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
}

void ALAI_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!BehaviourTreePtr && !BlackBoardDataPtr) return;

	UseBlackboard(BlackBoardDataPtr, BlackBoardComponent);
	RunBehaviorTree(BehaviourTreePtr);

	// Finding all TargetPoint Actors and adding them to the array
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), FoundActors);

	for (auto FoundActor : FoundActors)
	{
		auto TempActor = Cast<ATargetPoint>(FoundActor);
		TargetPointObjectPtrs.Add(TempActor);
	}
}

void ALAI_AIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIPerceptionComponent)
	{
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ALAI_AIController::OnPerceptionUpdated);
	}

	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ALAI_PlayerCharacter::StaticClass());
	PlayerCharacterPtr = Cast<ALAI_PlayerCharacter>(FoundActor);
	UE_LOG(LogTemplateCharacter, Log, TEXT("Found Actor: %s"), *PlayerCharacterPtr->GetName());
	BlackBoardComponent->SetValueAsObject("PlayerActor", PlayerCharacterPtr);
}

void ALAI_AIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor->IsA(ALAI_PlayerCharacter::StaticClass()))
	{
		if (!Stimulus.WasSuccessfullySensed())
		{
			if (BlackBoardComponent)
			{
				BlackBoardComponent->SetValueAsBool("bPlayerDetected", false);
			}
		}
		else
		{
			if (BlackBoardComponent)
			{
				BlackBoardComponent->SetValueAsBool("bPlayerDetected", true);
			}
		}
	}
}