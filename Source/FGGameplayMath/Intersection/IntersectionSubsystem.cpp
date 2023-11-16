// Fill out your copyright notice in the Description page of Project Settings.
#include "IntersectionSubsystem.h"
#include "IntersectionUtility.h"

void UIntersectionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UIntersectionSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for(const auto Demonstrator : IntersectionDemonstrators)
	{
		Demonstrator->Drawn = false;
	}
	
	if(IntersectionDemonstrators.Num() == 1)
	{
		IntersectionDemonstrators[0]->DrawShape(FColor::Green);
		return;
	}	

	for(const auto DemonstratorA : IntersectionDemonstrators)
	{
		for(const auto DemonstratorB : IntersectionDemonstrators)
		{
			if(DemonstratorA == DemonstratorB)
				continue;

			auto IntersectionTest = false;

			if(DemonstratorA->IntersectionType == EIntersection::Sphere &&
				DemonstratorB->IntersectionType == EIntersection::Sphere)
			{
				auto ContactPoint = FVector();
				
				IntersectionTest = UIntersectionUtility::SphereSphere(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->Radius,
					DemonstratorB->GetActorLocation(),
					DemonstratorB->Radius,
					ContactPoint
				);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);		
				}
			}

			if(DemonstratorA->IntersectionType == EIntersection::Sphere &&
				DemonstratorB->IntersectionType == EIntersection::Plane && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::SpherePlane(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->Radius,
					DemonstratorB->GetActorLocation(),
					DemonstratorB->GetActorUpVector(),
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}

			if(DemonstratorA->IntersectionType == EIntersection::Ray &&
				DemonstratorB->IntersectionType == EIntersection::Sphere && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::RaySphere(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->GetActorForwardVector(),
					DemonstratorB->GetActorLocation(),
					DemonstratorB->Radius,
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}

			if(DemonstratorA->IntersectionType == EIntersection::Ray && 
				DemonstratorB->IntersectionType == EIntersection::Plane && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::RayPlane(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->GetActorForwardVector(),
					DemonstratorB->GetActorUpVector(),
					DemonstratorB->GetActorLocation(),
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}

			if(DemonstratorA->IntersectionType == EIntersection::Ray && 
				DemonstratorB->IntersectionType == EIntersection::Triangle && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::RayTriangle(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->GetActorForwardVector(),
					DemonstratorB->GetActorTransform().TransformPosition(DemonstratorB->V0),
					DemonstratorB->GetActorTransform().TransformPosition(DemonstratorB->V1),
					DemonstratorB->GetActorTransform().TransformPosition(DemonstratorB->V2),
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}

			if(DemonstratorA->IntersectionType == EIntersection::Sphere &&
				DemonstratorB->IntersectionType == EIntersection::AABB && !IntersectionTest)
			{
				IntersectionTest = UIntersectionUtility::SphereAABB(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->Radius,
					DemonstratorB->GetActorLocation() + DemonstratorB->Min,
					DemonstratorB->GetActorLocation() + DemonstratorB->Max
					);
			}			

			if(DemonstratorA->IntersectionType == EIntersection::AABB &&
				DemonstratorB->IntersectionType == EIntersection::AABB && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::AABBIntersect(
					DemonstratorA->GetActorLocation() + DemonstratorA->Min,
					DemonstratorA->GetActorLocation() + DemonstratorA->Max,
					DemonstratorB->GetActorLocation() + DemonstratorB->Min,
					DemonstratorB->GetActorLocation() + DemonstratorB->Max,
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}

			if(DemonstratorA->IntersectionType == EIntersection::Ray &&
				DemonstratorB->IntersectionType == EIntersection::AABB && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::RayAABB(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->GetActorForwardVector(),
					DemonstratorB->GetActorLocation() + DemonstratorB->Min,
					DemonstratorB->GetActorLocation() + DemonstratorB->Max,
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}			
			
			if(IntersectionTest)
			{
				DemonstratorA->DrawShape(FColor::Red);
				DemonstratorB->DrawShape(FColor::Red);
			}
		}
	}

	for(const auto Demonstrator : IntersectionDemonstrators)
	{
		bool bOnScreen;
		
		if(Demonstrator->IntersectionType == EIntersection::AABB)
		{
			bOnScreen = UIntersectionUtility::AABBOnScreen(
				Demonstrator->Min,
				Demonstrator->Max,
				PlayerControllerInstance
				);
		}
		else
		{
			bOnScreen = UIntersectionUtility::IsOnScreen(
				PlayerControllerInstance,
				Demonstrator->GetActorLocation()
				); 
		}
		
		if(bOnScreen)
		{
			DrawDebugLine(
				GetWorld(),
				PlayerControllerInstance->GetPawn()->GetActorLocation(),
				Demonstrator->GetActorLocation(),
				FColor::Emerald
				);
			
			DrawDebugPoint(
				GetWorld(),
				Demonstrator->GetActorLocation(),
				25.f,
				FColor::Emerald
				);
		}
		
		if(!Demonstrator->Drawn)
			Demonstrator->DrawShape(FColor::Green);
	}	
}

void UIntersectionSubsystem::RegisterPlayerController(APlayerController* PlayerController)
{
	PlayerControllerInstance = PlayerController; 
}

void UIntersectionSubsystem::RegisterNoiseTerrain(ANoiseTerrain* NewNoiseTerrain)
{
	this->NoiseTerrain = NewNoiseTerrain;
}

void UIntersectionSubsystem::RegisterDemonstrator(AIntersectionDemonstrator* Demonstrator)
{
	if(!IntersectionDemonstrators.Contains(Demonstrator))
		IntersectionDemonstrators.Add(Demonstrator);
}

void UIntersectionSubsystem::UnregisterDemonstrator(AIntersectionDemonstrator* Demonstrator)
{
	if(IntersectionDemonstrators.Contains(Demonstrator))
		IntersectionDemonstrators.Remove(Demonstrator);
}

TStatId UIntersectionSubsystem::GetStatId() const
{
	return GetStatID();
}