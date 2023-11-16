// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "IntersectionDemonstrator.h"
#include "FGGameplayMath/Noise/NoiseTerrain.h"
#include "Subsystems/WorldSubsystem.h"
#include "IntersectionSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FGGAMEPLAYMATH_API UIntersectionSubsystem
	: public UTickableWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AIntersectionDemonstrator*> IntersectionDemonstrators;

	UPROPERTY()
	APlayerController* PlayerControllerInstance;

	UPROPERTY()
	ANoiseTerrain* NoiseTerrain;
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Tick(float DeltaTime) override;

	ANoiseTerrain* GetNoiseTerrain() const
	{
		return NoiseTerrain;
	}

	void RegisterPlayerController(APlayerController* PlayerController);

	void RegisterNoiseTerrain(ANoiseTerrain* NewNoiseTerrain);
	
	void RegisterDemonstrator(AIntersectionDemonstrator* Demonstrator);
	void UnregisterDemonstrator(AIntersectionDemonstrator* Demonstrator);

	virtual TStatId GetStatId() const override;
};