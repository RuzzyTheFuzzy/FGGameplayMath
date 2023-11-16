// Fill out your copyright notice in the Description page of Project Settings.
#include "CollisionSubsystem.h"
#include "FGGameplayMath/Constants.h"
#include "FGGameplayMath/Intersection/IntersectionUtility.h"

void UCollisionSubsystem::RegisterDemonstrator(ACollisionDemonstrator* Demonstrator)
{
	if(!CollisionDemonstrators.Contains(Demonstrator))
		CollisionDemonstrators.Add(Demonstrator);
}

void UCollisionSubsystem::UnregisterDemonstrator(ACollisionDemonstrator* Demonstrator)
{
	if(CollisionDemonstrators.Contains(Demonstrator))
		CollisionDemonstrators.Remove(Demonstrator);
}

TStatId UCollisionSubsystem::GetStatId() const
{
	return GetStatID();
}

void UCollisionSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update Positions
	for(const auto Demonstrator : CollisionDemonstrators)
	{
		if(Demonstrator->ApplyGravity)
			Demonstrator->AddForce(GGravity);
		
		Demonstrator->Step(DeltaTime);
	}

	// Resolve Collisions
	for(const auto DemonstratorA : CollisionDemonstrators)
	{
		for(const auto DemonstratorB : CollisionDemonstrators)
		{
			if(DemonstratorA == DemonstratorB)
				continue;

			if(DemonstratorA->CollisionType == ECollisionType::SphereCollider)
			{
				FVector ContactPoint;
				
				if(DemonstratorB->CollisionType == ECollisionType::SphereCollider)
				{
					if(UIntersectionUtility::SphereSphere(
						DemonstratorA->GetActorLocation(),
						DemonstratorA->GetRadius(),
						DemonstratorB->GetActorLocation(),
						DemonstratorB->GetRadius(),
						ContactPoint))
					{
						DemonstratorA->AddForce(-DemonstratorA->Velocity * 2.f);
						DrawDebugPoint(GetWorld(), ContactPoint, 25.f, FColor::Purple, false, 1.5f);
					}									
				}

				if(DemonstratorB->CollisionType == ECollisionType::PlaneCollider)
				{
					if(UIntersectionUtility::SpherePlane(
						DemonstratorA->GetActorLocation(),
						DemonstratorA->GetRadius(),
						DemonstratorB->GetActorLocation(),
						DemonstratorB->GetActorUpVector(),
						ContactPoint))
					{
						DemonstratorA->AddForce(-DemonstratorA->Velocity * 2.f);
						DrawDebugPoint(GetWorld(), ContactPoint, 25.f, FColor::Purple, false, 1.5f);
					}
				}
			}
		}
	}
}