#pragma once

#include "VerletNode.generated.h"

USTRUCT()
struct FVerletNode
{
	GENERATED_BODY()

	FVector Location;
	FVector OldLocation;

	FVerletNode()
	{
		OldLocation = Location = FVector::ZeroVector;
	}
	
	FVerletNode(const FVector& Position)
	{
		this->Location = Position;
		OldLocation = Position;
	};
};