// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpolator.h"
#include "Engine/DataAsset.h"
#include "InterpolatorAsset.generated.h"

/**
 * 
 */
UCLASS()
class FGGAMEPLAYMATH_API UInterpolatorAsset
	: public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FInterpolator Interpolator;
};
