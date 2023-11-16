#pragma once

#include "RopeSweepInfo.generated.h"

USTRUCT()
struct FRopeSweepInfo
{
	GENERATED_BODY()

	// Pointer to colliding primitive component
	TWeakObjectPtr<UPrimitiveComponent> Component;
	
	// Indices of all nodes that registered an impact with this component
	TArray<int32> NodeIndices;
};
