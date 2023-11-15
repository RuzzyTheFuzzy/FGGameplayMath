// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "VerletNode.h"
#include "RopeSweepInfo.h"
#include "Rope.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FGGAMEPLAYMATH_API URope
	: public UProceduralMeshComponent
{
	GENERATED_BODY()

	int32 CollisionCount;
	
	TArray<FVerletNode> Nodes;
	TArray<FOverlapResult> TraceBuffer;
	TArray<FRopeSweepInfo> SweepInfos;

	FCollisionShape TraceShape;
	
	float TimeAccumulation;

	void Simulate();
	void ApplyConstraints();
	void AdjustCollisions();
	void SnapshotCollision();
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 TotalNodes = 200;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Iterations = 80;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float NodeDistance = 10.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StepTime = .01f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxStep = .1f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Gravity = FVector(0.f, 0.f, -2000.f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CollisionRadius = 10.f;

	URope(const FObjectInitializer& ObjectInitializer);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};