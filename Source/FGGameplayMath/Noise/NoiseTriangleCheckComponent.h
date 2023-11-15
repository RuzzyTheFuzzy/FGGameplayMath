// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "NoiseTerrain.h"
#include "Components/ActorComponent.h"
#include "NoiseTriangleCheckComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FGGAMEPLAYMATH_API UNoiseTriangleCheckComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ANoiseTerrain* NoiseTerrainActor;

public:
	UNoiseTriangleCheckComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
