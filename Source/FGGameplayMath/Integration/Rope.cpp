// Fill out your copyright notice in the Description page of Project Settings.
#include "Rope.h"
#include "DrawDebugHelpers.h"

URope::URope(const FObjectInitializer& ObjectInitializer) : UProceduralMeshComponent(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	CollisionCount = 0;
	TimeAccumulation = 0.f;
	TraceShape = FCollisionShape::MakeSphere(CollisionRadius);
	Nodes.Init(FVerletNode(), TotalNodes);
}

void URope::BeginPlay()
{
	Super::BeginPlay();

	auto Location = GetOwner()->GetActorLocation();

	for(int i = 0; i < TotalNodes; i++)
	{
		Nodes[i] = FVerletNode(Location);
		Location.Z -= NodeDistance;
	}
}

void URope::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SnapshotCollision();

	TimeAccumulation += DeltaTime;
	TimeAccumulation = FMath::Min(TimeAccumulation, MaxStep);

	while(TimeAccumulation >= StepTime)
	{
		Simulate();

		for(int i = 0; i < Iterations; i++)
		{
			ApplyConstraints();
			//AdjustCollisions();
		}

		TimeAccumulation -= StepTime;
	}

	for(const auto Node : Nodes)
	{
		DrawDebugPoint(
			GetWorld(),
			Node.Location,
			NodeDistance * .5f,
			FColor::Green
			);
	}
}

void URope::Simulate()
{
	for (int i = 0; i < Nodes.Num(); i++)
	{
		const auto Temp = Nodes[i].Location;
		Nodes[i].Location += (Nodes[i].Location - Nodes[i].OldLocation) + Gravity * StepTime * StepTime;
		Nodes[i].OldLocation = Temp;
	}
}

void URope::ApplyConstraints()
{
	for (int i = 0; i < Nodes.Num() - 1; i++)
	{
		const float DiffX = Nodes[i].Location.X - Nodes[i + 1].Location.X;
		const float DiffY = Nodes[i].Location.Y - Nodes[i + 1].Location.Y;
		const float DiffZ = Nodes[i].Location.Z - Nodes[i + 1].Location.Z;

		const float Distance = FVector::Distance(Nodes[i].Location, Nodes[i + 1].Location);

		float Difference = 0;

		if (Distance > 0)
		{ 
			Difference = (NodeDistance - Distance) / Distance;
		}

		const FVector Translate = FVector(DiffX, DiffY, DiffZ) * (.5f * Difference);

		if (i == 0)
		{
			Nodes[i].Location = GetOwner()->GetActorLocation();
		}
		else
		{
			Nodes[i].Location += Translate;
		}
		
		Nodes[i + 1].Location -= Translate;
	}
}

void URope::SnapshotCollision()
{
	SweepInfos.Empty();
	
	for (int i = 0; i < Nodes.Num(); i++)
	{
		auto SweepBuffer = TArray<FHitResult>();

		GetWorld()->SweepMultiByChannel(
			SweepBuffer,
			Nodes[i].OldLocation,
			Nodes[i].Location,
			FQuat::Identity,
			ECC_WorldStatic,
			TraceShape
			);

		if(SweepBuffer.Num() > 0)
		{
			DrawDebugSphere(
				GetWorld(),
				Nodes[i].Location,
				TraceShape.GetSphereRadius(),
				8,
				FColor::Red
				);					
		
			auto NewSweepInfo = FRopeSweepInfo();
			NewSweepInfo.Index = i;

			auto ClosestDistance = TNumericLimits<float>::Min();

			for(int s = 0; s < SweepBuffer.Num(); s++)
			{
				const auto HitPoint = SweepBuffer[s];

				if(HitPoint.Distance < ClosestDistance)
				{
					NewSweepInfo.ImpactPoint = HitPoint.ImpactPoint;
					ClosestDistance = HitPoint.Distance;
				}
			}

			DrawDebugPoint(
				GetWorld(),
				NewSweepInfo.ImpactPoint,
				15.f,
				FColor::Cyan
				);

			SweepInfos.Add(NewSweepInfo);
		}
		else
		{
			DrawDebugSphere(
			GetWorld(),
			Nodes[i].Location,
			TraceShape.GetSphereRadius(),
			8,
			FColor::Green
			);			
		}
     }
}

void URope::AdjustCollisions()
{
	for (int i = 0; i < SweepInfos.Num(); i++)
	{
		const auto SweepInfo = SweepInfos[i];

		const FVector NodeLocation = Nodes[SweepInfo.Index].Location;
		const FVector OldNodeLocation = Nodes[SweepInfo.Index].OldLocation;
		
		const FVector CollisionLocation = SweepInfo.ImpactPoint;

		const auto Distance = FVector::Distance(CollisionLocation, NodeLocation);

		if(Distance - CollisionRadius > CollisionRadius)
			continue;

		const FVector Direction = NodeLocation - CollisionLocation;
				
		// Apply intersection as new position
		Nodes[SweepInfo.Index].Location = OldNodeLocation + (Direction.GetSafeNormal() * Distance);
	}
}