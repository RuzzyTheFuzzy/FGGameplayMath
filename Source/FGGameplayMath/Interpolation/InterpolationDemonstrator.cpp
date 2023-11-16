// Fill out your copyright notice in the Description page of Project Settings.
#include "InterpolationDemonstrator.h"

AInterpolationDemonstrator::AInterpolationDemonstrator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInterpolationDemonstrator::BeginPlay()
{
	Super::BeginPlay();
	Interpolator->Interpolator.Initialize();
	Origin = GetActorLocation();
}

void AInterpolationDemonstrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Make sure Goal gets updated, if someone changes TargetPosition at runtime; shouldn't normally be needed.
	Goal = Origin + TargetPosition;
	
	Interpolator->Interpolator.Update(DeltaTime);

	const auto T = Interpolator->Interpolator.GetValue();
	const auto MoveVector = FMath::Lerp(Origin, Goal, T);

	SetActorLocation(MoveVector);
}