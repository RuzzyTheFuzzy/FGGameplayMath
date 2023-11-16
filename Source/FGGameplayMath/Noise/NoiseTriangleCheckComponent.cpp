// Fill out your copyright notice in the Description page of Project Settings.
#include "NoiseTriangleCheckComponent.h"

#include "FGGameplayMath/Intersection/IntersectionSubsystem.h"
#include "FGGameplayMath/Intersection/ShapeDrawUtility.h"

UNoiseTriangleCheckComponent::UNoiseTriangleCheckComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNoiseTriangleCheckComponent::BeginPlay()
{
	Super::BeginPlay();
	NoiseTerrainActor = GetWorld()->GetSubsystem<UIntersectionSubsystem>()->GetNoiseTerrain();
}

void UNoiseTriangleCheckComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(NoiseTerrainActor)
	{
		const auto Location =
			GetOwner()->GetActorLocation();
		
		TArray<FVector> Quad;
		NoiseTerrainActor->FindClosestQuad(Location, Quad);
		UShapeDrawUtility::Quad(
			GetWorld(),
			Quad[0],
			Quad[1],
			Quad[2],
			Quad[3],
			FColor::Green
			);
	}
}