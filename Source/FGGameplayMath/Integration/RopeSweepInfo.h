#pragma once

#include "RopeSweepInfo.generated.h"

USTRUCT()
struct FRopeSweepInfo
{
	GENERATED_BODY()

	// Index of the node that registered these impacts
	int32 Index;

	// Distance to impact point
	float Distance;

	// The closest impact registered
	FVector ImpactPoint;
};
